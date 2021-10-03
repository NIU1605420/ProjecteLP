using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Runtime.InteropServices;
using System.Windows;
using Windows.Devices.Geolocation;
using Windows.UI.Xaml.Controls.Maps;
using LP_OSM_2122_WPF;
using Windows.Storage.Streams;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using System.Drawing;
using System.Windows.Input;

namespace LS_OSM_2122_WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct PoiBridge
        {
            public int i;
            public double lat;
            public double lon;
            public int color;
            public IntPtr title;
        }

        public struct Way
        {
            public double[] lat;
            public double[] lon;
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate IntPtr AllocateResultOfStrategyArray(IntPtr length);

        [DllImport("LP-OSM-2122-DLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void loadOSMData(char[] map);

        [DllImport("LP-OSM-2122-DLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void renderPois(AllocateResultOfStrategyArray allocator);

        [DllImport("LP-OSM-2122-DLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern bool renderWays(int offset, AllocateResultOfStrategyArray allocatorLats, AllocateResultOfStrategyArray allocatorLons);

        [DllImport("LP-OSM-2122-DLL.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void shortestPath(int idxFrom, int idxTo, AllocateResultOfStrategyArray allocatorLats, AllocateResultOfStrategyArray allocatorLons);

        private MapElementsLayer elementsLayer;
        private static BackgroundWorker backgroundWorker;
        private static BackgroundWorker backgroundWorker4CamiMesCurt;
        private FileSystemWatcher watcher;

        private PoiBridge[] poiBridges = new List<PoiBridge>().ToArray();
        private List<Way> ways = new List<Way>();


        private int idxFrom;
        private int idxTo;            

        private static char[] loadedMap;

        public MainWindow()
        {
            InitializeComponent();

            InitializeMap();
            InitializeLog();
            InitializeWorker();

            // 2nd part
            InitializeWorkerForCamiMesCurt();
        }

        // Prepara mapa amb el Tile de OSM
        private void InitializeMap()
        {
            elementsLayer = new MapElementsLayer();
            MapTileSource tileSource = new MapTileSource(new HttpMapTileDataSource("https://tile.openstreetmap.org/${z}/${x}/${y}.png"));
            tileSource.Visible = true;
            tileSource.Layer = MapTileLayer.BackgroundReplacement;
            mapControl.TileSources.Clear();
            mapControl.TileSources.Add(tileSource);
            mapControl.ZoomLevel = 51;
            mapControl.Layers = new List<MapLayer> { elementsLayer };
        }

        // Prepara Log, on permetria llegir un fitxer que s'escriu a dins de la DLL
        private void InitializeLog()
        {
            watcher = new FileSystemWatcher();
            watcher.Path = ".";
            watcher.Filter = "Log.txt";
            watcher.Changed += Watcher_Changed;
            watcher.EnableRaisingEvents = true;
            watcher.NotifyFilter = NotifyFilters.LastWrite;
        }

        // Prepara Thread per carrega de OSM
        private void InitializeWorker()
        {
            backgroundWorker = new BackgroundWorker();
            backgroundWorker.DoWork += BackgroundWorker_DoWork;
            backgroundWorker.RunWorkerCompleted += BackgroundWorker_RunWorkerCompleted;
        }

        // Prepara Thread per calcul de cami mes curt
        private void InitializeWorkerForCamiMesCurt()
        {
            backgroundWorker4CamiMesCurt = new BackgroundWorker();
            backgroundWorker4CamiMesCurt.DoWork += BackgroundWorker4CamiMesCurt_DoWork;
            backgroundWorker4CamiMesCurt.RunWorkerCompleted += BackgroundWorker4CamiMesCurt_RunWorkerCompleted;
        }

        // Listener que el Thread del Cami Mes Curt ja ha finalitzat
        private void BackgroundWorker4CamiMesCurt_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            logText.Text += "Acabat algoritme del calcul camí més curt.";
        }

        // Carrega del treball del Thread Calcul del Cami Mes Curt
        private void BackgroundWorker4CamiMesCurt_DoWork(object sender, DoWorkEventArgs e)
        {
            List<Way> camiMesCurt = new List<Way>();

            if (idxFrom == idxTo) {
                return;
            }

            using (var pLat = new PinnedArray<double>())
            {
                using (var pLon = new PinnedArray<double>())
                {
                    shortestPath(idxFrom, idxTo, pLat.CreateArray, pLon.CreateArray);
                    Way shortestWay = new Way { lat = pLat.Array, lon = pLon.Array };
                    camiMesCurt.Add(shortestWay);
                }
            }

            if (camiMesCurt.Count > 0) { 
                ways = camiMesCurt;
            }

        }

        // Listener que el Thread de Carrega OSM ja ha acabat
        private void BackgroundWorker_RunWorkerCompleted(object sender, RunWorkerCompletedEventArgs e)
        {
            logText.Text += "Acabat process de carrega. Ja pots visualitzar.";
            this.Cursor = Cursors.Arrow;
            mapControl.Cursor = Cursors.Arrow;

            foreach ( PoiBridge poiBridge in poiBridges){
                cmbFromPois.Items.Add(Marshal.PtrToStringAnsi(poiBridge.title));
                cmbToPois.Items.Add(Marshal.PtrToStringAnsi(poiBridge.title));
            }

            if (cmbFromPois.Items.Count > 0 && cmbToPois.Items.Count > 0) {
                cmbFromPois.SelectedIndex = 0;
                cmbToPois.SelectedIndex = 0;
            }
        }

        // Carrega de treball de carrega del OSM  
        private void BackgroundWorker_DoWork(object sender, DoWorkEventArgs e)
        {
            loadOSMData(loadedMap);

            using (var pa = new PinnedArray<PoiBridge>())
            {
                renderPois(pa.CreateArray);
                poiBridges = pa.Array;
            }

            bool nextWay = false;
            int i = 0;

            do
            {
                using (var pLat = new PinnedArray<double>())
                {
                    using (var pLon = new PinnedArray<double>())
                    {
                        nextWay = renderWays(i, pLat.CreateArray, pLon.CreateArray);
                        Way way = new Way { lat = pLat.Array, lon = pLon.Array };
                        ways.Add(way);
                        i++;
                    }
                }
            } while (nextWay);
        }

        // Transformar color a tipus stream, tipat que espera el MapControl 
        private async Task<InMemoryRandomAccessStream> CreateInMemoryImageStream(Color fillColor, uint heightInPixel, uint widthInPixel)
        {
            var stream = new InMemoryRandomAccessStream();

            var encoder = await BitmapEncoder.CreateAsync(BitmapEncoder.JpegEncoderId, stream);

            List<Byte> bytes = new List<byte>();
            for (int x = 0; x < widthInPixel; x++)
            {
                for (int y = 0; y < heightInPixel; y++)
                {
                    bytes.Add(fillColor.R);
                    bytes.Add(fillColor.G);
                    bytes.Add(fillColor.B);
                    bytes.Add(fillColor.A);
                }
            }

            encoder.SetPixelData(BitmapPixelFormat.Rgba8, BitmapAlphaMode.Ignore, widthInPixel, heightInPixel, 96, 96, bytes.ToArray());
            await encoder.FlushAsync();
            return stream;
        }

        // Representa punt de interes amb color definit per l'Stream
        private MapIcon Representa_MapIcon(double latitude, double longitude, string title, InMemoryRandomAccessStream markerImage)
        {
            MapIcon mapIcon = new MapIcon { Image = RandomAccessStreamReference.CreateFromStream(markerImage), Location = new Geopoint(new BasicGeoposition { Latitude = latitude, Longitude = longitude }), Title = title };

            return mapIcon;
        }

        private void Watcher_Changed(object sender, FileSystemEventArgs e)
        {
            watcher.EnableRaisingEvents = false;

            this.Dispatcher.BeginInvoke(new Action(() => {
                FileStream fileStream = new FileStream("Log.txt", FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                StreamReader reader = new StreamReader(fileStream);

                logText.Text += "\n" + reader.ReadToEnd();

                reader.Close();

                watcher.EnableRaisingEvents = true;
            }));
        }

        // Inici del Thread calcul del Cami Mes Curt
        private void ShortestPath_Click(object sender, RoutedEventArgs e)
        {
            idxFrom = cmbFromPois.SelectedIndex;
            idxTo = cmbToPois.SelectedIndex;
            if (idxFrom == idxTo) {
                return;
            }
            backgroundWorker4CamiMesCurt.RunWorkerAsync();
        }

        // Visualitza Punts De Interes que s'han carregat anteriorment
        private async void VisualitzaPdis_Click(object sender, RoutedEventArgs e)
        {
            List<MapElement> mapElements = new List<MapElement>();

            foreach (var item in poiBridges)
            {
                var icon = await Task.Run(() => {
                    int color = item.color;
                    return CreateInMemoryImageStream(Color.FromArgb((color >> 16) & 0xff, (color >> 8) & 0xff, (color) & 0xff), 10, 10);
                });
                mapElements.Add(Representa_MapIcon(item.lat, item.lon, Marshal.PtrToStringAnsi(item.title), icon));
            }

            mapElements.AddRange(elementsLayer.MapElements);

            elementsLayer.MapElements = mapElements;
        }

        // Visualitza Camins que s'han carregat anteriorment
        private void VisualitzaCamins_Click(object sender, RoutedEventArgs e)
        {
            List<MapElement> mapElements = new List<MapElement>();

            foreach (var way in ways)
            {
                Dispatcher.Invoke(() =>
                {
                    MapPolyline mapPolyline = new MapPolyline();

                    List<BasicGeoposition> basicGeopositions = new List<BasicGeoposition>();

                    for (int i = 0; i < way.lat.Length; i++)
                    {
                        basicGeopositions.Add(new BasicGeoposition { Latitude = way.lat[i], Longitude = way.lon[i] });
                    }

                    mapPolyline.StrokeColor = Windows.UI.Colors.Green;
                    mapPolyline.StrokeThickness = 3;
                    mapPolyline.StrokeDashed = false;
                    mapPolyline.Path = new Geopath(basicGeopositions);

                    mapElements.Add(mapPolyline);
                });
            }

            mapElements.AddRange(elementsLayer.MapElements);

            elementsLayer.MapElements = mapElements;
        }

        // Neteja dels elements que formen en el mapa
        private void Clear_Click(object sender, RoutedEventArgs e)
        {
            elementsLayer.MapElements = new List<MapElement>();
        }

        // Punt d'inici de carrega del fitxer OSM. Neteja tots els elements i fa un clear de les dades emmagatzemades. 
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            bool showDialog = (bool)openFileDialog.ShowDialog();

            if (showDialog)
            {
                poiBridges = new List<PoiBridge>().ToArray();
                ways.Clear();
                cmbFromPois.Items.Clear();
                cmbToPois.Items.Clear();

                elementsLayer.MapElements = new List<MapElement>();

                string fileName = openFileDialog.FileName + "\0";
                loadedMap = fileName.ToCharArray();

                logText.Text = "Carregant...";
                this.Cursor = Cursors.Wait;
                mapControl.Cursor = Cursors.Wait;
                backgroundWorker.RunWorkerAsync();
            }
            else
            {
                logText.Text = "Error en carregar el fitxer. Prova un altre.";
            }
        }

    }
}
