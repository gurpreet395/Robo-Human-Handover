using Microsoft.Kinect;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO;



namespace KinectCoordinateMapping
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        KinectSensor _sensor;
        MultiSourceFrameReader _reader;
        IList<Body> _bodies;



  
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            _sensor = KinectSensor.GetDefault();

            if (_sensor != null)
            {
                _sensor.Open();

                _reader = _sensor.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Depth | FrameSourceTypes.Infrared | FrameSourceTypes.Body);
                _reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
            }
        }

        private void Window_Closed(object sender, EventArgs e)
        {
            if (_reader != null)
            {
                _reader.Dispose();
            }

            if (_sensor != null)
            {
                _sensor.Close();
            }
        }

        void Reader_MultiSourceFrameArrived(object sender, MultiSourceFrameArrivedEventArgs e)
        {
            var reference = e.FrameReference.AcquireFrame();

            // Color
            using (var frame = reference.ColorFrameReference.AcquireFrame())
            {
                if (frame != null)
                {

                }
            }

            // Depth
            using (var frame = reference.DepthFrameReference.AcquireFrame())
            {
                if (frame != null)
                {

                }
            }

            // Infrared
            using (var frame = reference.InfraredFrameReference.AcquireFrame())
            {
                if (frame != null)
                {

                }
            }

            // Body
            using (var frame = reference.BodyFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    canvas.Children.Clear();

                    _bodies = new Body[frame.BodyFrameSource.BodyCount];

                    frame.GetAndRefreshBodyData(_bodies);

                    foreach (var body in _bodies)
                    {
                        if (body.IsTracked)
                        {
                        // COORDINATE MAPPING


                        Loop:
                            foreach (Joint joint in body.Joints.Values)
                            {
                                if (joint.TrackingState == TrackingState.Tracked)
                                {

                                    if (joint.TrackingState == TrackingState.Tracked)
                                    {
                                        Joint head = body.Joints[JointType.SpineMid];
                                        Joint hand = body.Joints[JointType.HandTipRight];

                                        float sx = head.Position.X;
                                        float sy = head.Position.Y;
                                        float sz = head.Position.Z;
                                        float hx = hand.Position.X;
                                        float hy = hand.Position.Y;
                                        float hz = hand.Position.Z;
                                      
                                        double sxi = (sx + 0.25);
                                        double syi = (sy + 0.20);
                                        double szi = (sz + 0.16 - 0.60);
                                        double hxi = (hx +0.25);
                                        double hyi = (hy);
                                        double hzi = (hz + 0.16-0.20);


                                        try
                                        {
                                            StreamWriter writer = new StreamWriter("E:\\xampp/htdocs/Spine.txt");
                                            System.Threading.Thread.Sleep(5);

                                            writer.WriteLine(szi + " " + sxi + " " + syi);

                                            writer.Close();

                                            StreamWriter writer2 = new StreamWriter("E:\\xampp/htdocs/Hand.txt");
                                            writer2.WriteLine(hzi + " " + hxi + " " + hyi);

                                            writer2.Close();
                                        }

                                        catch (System.IO.IOException f)
                                        { goto Loop; }

                                        finally
                                        {
                                            
                                        }




                                    }
                                    // 3D space point


                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
                                                    
                    
             
            
        
    
