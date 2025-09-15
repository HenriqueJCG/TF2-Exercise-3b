#include "rclcpp/rclcpp.hpp"

#include "visualization_msgs/msg/marker.hpp"
#include "visualization_msgs/msg/marker_array.hpp"
#include "geometry_msgs/msg/pose.hpp"


class ObjectInfo {
private:
    std::string objPath;
    unsigned int id;
    geometry_msgs::msg::Pose pose;
    double scale;
    double r;
    double g;
    double b;
public:
    inline void setObjPath(std::string p) {objPath=p;}
    inline std::string getObjPath() {return objPath;}

    inline void setObjID(unsigned int i) {id=i;}
    inline unsigned int getObjID() {return id;}
    inline double getx() {return pose.position.x;}
    inline double gety() {return pose.position.y;}
    inline double getz() {return pose.position.z;}
    inline double getqx() {return pose.orientation.x;}
    inline double getqy() {return pose.orientation.y;}
    inline double getqz() {return pose.orientation.z;}
    inline double getqw() {return pose.orientation.w;}
    inline void setx(double v) {pose.position.x=v;}
    inline void sety(double v) {pose.position.y=v;}
    inline void setz(double v) {pose.position.z=v;}
    inline void setqx(double v) {pose.orientation.x=v;}
    inline void setqy(double v) {pose.orientation.y=v;}
    inline void setqz(double v) {pose.orientation.z=v;}
    inline void setqw(double v) {pose.orientation.w=v;}
    inline double getr() {return r;}
    inline double getg() {return g;}
    inline double getb() {return b;}
    inline double getscale() {return scale;}
    inline void setr(double v) {r=v;}
    inline void setg(double v) {g=v;}
    inline void setb(double v) {b=v;}
    inline void setscale(double v) {scale=v;}
};


using namespace std::chrono_literals;
using std::placeholders::_1;

class MarkerPublisherNode : public rclcpp::Node
{
public:
  MarkerPublisherNode()
  : Node("marker_publisher_node")
  {
    publisher_ = create_publisher<visualization_msgs::msg::MarkerArray>("visualization_marker_array", 10);
    timer_ = create_wall_timer(
      500ms, std::bind(&MarkerPublisherNode::timer_callback, this));
    SetWorld();
  }

  void timer_callback()
  {
    visualization_msgs::msg::Marker marker;

    RCLCPP_DEBUG(get_logger(), "LOADING %ld OBJECTS", objects.size());

    markers_message_.markers.clear();
        
    for(uint i=0; i<objects.size(); i++) {
        marker.header.frame_id = "assembly_frame";
        marker.header.stamp =  this->get_clock()->now();
        marker.ns = "assembly_objects";
        marker.id = objects[i].getObjID();
        marker.mesh_resource = objects[i].getObjPath();

        marker.type = visualization_msgs::msg::Marker::MESH_RESOURCE;
        marker.action = visualization_msgs::msg::Marker::ADD;

        marker.pose.position.x = objects[i].getx();
        marker.pose.position.y = objects[i].gety();
        marker.pose.position.z = objects[i].getz();
        marker.pose.orientation.x = objects[i].getqx();
        marker.pose.orientation.y = objects[i].getqy();
        marker.pose.orientation.z = objects[i].getqz();
        marker.pose.orientation.w = objects[i].getqw();
        marker.scale.x = objects[i].getscale();
        marker.scale.y = objects[i].getscale();
        marker.scale.z = objects[i].getscale();
        marker.color.a = 1.0; // Don't forget to set the alpha!
        marker.color.r = objects[i].getr();
        marker.color.g = objects[i].getg();
        marker.color.b = objects[i].getb();
            
           
        RCLCPP_DEBUG(get_logger(), "OBJECT: [%d]", marker.id);
        RCLCPP_DEBUG(get_logger(), "X value is: [%f]", marker.pose.position.x);
        RCLCPP_DEBUG(get_logger(), "Y value is: [%f]", marker.pose.position.y);
        RCLCPP_DEBUG(get_logger(), "Z value is: [%f]", marker.pose.position.z);

        RCLCPP_DEBUG(get_logger(), "ORI X value is: [%f]", marker.pose.orientation.x);
        RCLCPP_DEBUG(get_logger(), "ORI Y value is: [%f]", marker.pose.orientation.y);
        RCLCPP_DEBUG(get_logger(), "ORI Z value is: [%f]", marker.pose.orientation.z);
        RCLCPP_DEBUG(get_logger(), "ORI W value is: [%f]", marker.pose.orientation.w);

        markers_message_.markers.push_back(marker);
    }

    publisher_->publish(markers_message_);
  }


  void SetWorld()
  {
    ObjectInfo obj;

    obj.setObjPath("package://rviz2_marker_demo/objects/fixtures/Wooden_Plate.dae");
    obj.setObjID(2);
    obj.setx(0.41);
    obj.sety(0);
    obj.setz(0.015);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);
    

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/Window.stl");
    obj.setObjID(3);
    obj.setx(0.5);
    obj.sety(-0.42);
    obj.setz(0);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/Chassis.stl");
    obj.setObjID(4);
    obj.setx(0.5);
    obj.sety(-0.32);
    obj.setz(0.05);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/BottomWing.stl");
    obj.setObjID(5);
    obj.setx(0.3);
    obj.sety(-0.32);
    obj.setz(0);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/FrontWheel.stl");
    obj.setObjID(6);
    obj.setx(0.35);
    obj.sety(-0.4);
    obj.setz(0);
    obj.setqx(sin(M_PI /4));
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(cos(M_PI /4));
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/MotorGrill.stl");
    obj.setObjID(7);
    obj.setx(0.35);
    obj.sety(-0.46);
    obj.setz(0);
    obj.setqx(sin(M_PI /2));
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(cos(M_PI /2));
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/Propeller.stl");
    obj.setObjID(8);
    obj.setx(0.2);
    obj.sety(-0.43);
    obj.setz(0);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/RearWheelLeft.stl");
    obj.setObjID(9);
    obj.setx(0.12);
    obj.sety(-0.3);
    obj.setz(0);
    obj.setqx(0);
    obj.setqy(sin(-M_PI /4));
    obj.setqz(0);
    obj.setqw(cos(-M_PI /4));
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/RearWheelRight.stl");
    obj.setObjID(10);
    obj.setx(0.12);
    obj.sety(-0.35);
    obj.setz(0);
    obj.setqx(0);
    obj.setqy(sin(-M_PI /4));
    obj.setqz(0);
    obj.setqw(cos(-M_PI /4));
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/RearWing.stl");
    obj.setObjID(11);
    obj.setx(0.2);
    obj.sety(0.3);
    obj.setz(0.01);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/TopWing.stl");
    obj.setObjID(12);
    obj.setx(0.2);
    obj.sety(0.45);
    obj.setz(0);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(sin(M_PI /4));
    obj.setqw(cos(M_PI /4));
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/UnderBody.stl");
    obj.setObjID(13);
    obj.setx(0.4);
    obj.sety(0.4);
    obj.setz(0.01);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(0);
    obj.setqw(1);
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);

    obj.setObjPath("package://rviz2_marker_demo/objects/plane/UpperBody.stl");
    obj.setObjID(14);
    obj.setx(0.5);
    obj.sety(0.4);
    obj.setz(0.01);
    obj.setqx(0);
    obj.setqy(0);
    obj.setqz(sin(M_PI /4));
    obj.setqw(cos(M_PI /4));
    obj.setr((double)rand() / (double)RAND_MAX);
    obj.setg((double)rand() / (double)RAND_MAX);
    obj.setb((double)rand() / (double)RAND_MAX);
    obj.setscale(1.0);
    objects.push_back(obj);
  }

private:
  rclcpp::Publisher<visualization_msgs::msg::MarkerArray>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
  std::vector<ObjectInfo> objects;
  visualization_msgs::msg::MarkerArray markers_message_;
};


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = std::make_shared<MarkerPublisherNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
