#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

using namespace std::chrono_literals;
 
class RobotNewsStationNode : public rclcpp::Node // MODIFY NAME
{
public:
    RobotNewsStationNode() : Node("robot_news_station") // MODIFY NAME
    {
        this->declare_parameter("robot_name","R2D2");
        robot_name_ = this->get_parameter("robot_name").as_string();
        publisher_ = this -> create_publisher<example_interfaces::msg::String>("robot_news", 10);
        timer_ = this -> create_wall_timer(0.5s, std::bind(&RobotNewsStationNode::publishNews, this));
        RCLCPP_INFO(this -> get_logger(), "Robot News Station has been Started");
    }
 
private:
    void publishNews(){
        auto msg = example_interfaces::msg::String();
        msg.data = std::string("Hi, this is ") + robot_name_ + std::string(" from Robot News Station");
        publisher_ -> publish(msg);
    }

    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>(); // MODIFY NAME
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}