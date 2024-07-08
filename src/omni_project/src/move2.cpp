//實際程式架構，積分(初版草稿)
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>

//最大速度m/s
#define speed 0.3
geometry_msgs::Twist vel;

//回傳位置
void Callback(geometry_msgs::Twist input_vel){

    vel.linear.x = input_vel.linear.x;
    vel.linear.y = input_vel.linear.y;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "move2");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("run",1);
    ros::Subscriber sub = nh.subscribe("velocity",10,Callback);

    ros::Rate loop_rate(10);

    geometry_msgs::Twist output_vel;
    geometry_msgs::Point target;
    geometry_msgs::Point start;
    
    int count = 1;

    double location_x = 0, location_y = 0;
    
    while(ros::ok() && count <= 5){

        ros::spinOnce();

        switch(count){
            //目標點-單位cm
            case 1:
                target.x = 140;
                target.y = 0;
                start.x = 0;
                start.y = 0;
                break;
            case 2:
                target.x = 140;
                target.y = 47.5;
                start.x = 140;
                start.y = 0;
                break;
            case 3:
                target.x = 250;
                target.y = 47.5;
                start.x = 140;
                start.y = 47.5;
                break;
            case 4:
                target.x = 250;
                target.y = 5;
                start.x = 250;
                start.y = 47.5;
                break;
            case 5:
                target.x = 400;
                target.y = 5;
                start.x = 250;
                start.y = 5;
                break;
            default:
                break;
        }

        //使用速度換算距離-0.1為頻率的倒數，即時間
        location_x += vel.linear.x * 100 * 0.01;
        location_y += vel.linear.y * 100 * 0.01;
        double last_x = (target.x - location_x), last_y = (target.y - location_y);
        double distance_x = std::abs(target.x - start.x), distance_y = std::abs(target.y - start.y);

        if(target.x == start.x)
            distance_x = 1;

        if(target.y == start.y)
            distance_y = 1;

        //依離目標點的位置減少速度
        output_vel.linear.x = speed * (last_x / distance_x);
        output_vel.linear.y = speed * (last_y / distance_y);

        if(std::abs(output_vel.linear.x) <= 0.01 && output_vel.linear.x > 0)
            output_vel.linear.x = 0.01;

        else if(std::abs(output_vel.linear.x) <= 0.01 && output_vel.linear.x < 0)
        output_vel.linear.x = -0.01;

         if(std::abs(output_vel.linear.y) <= 0.01 && output_vel.linear.y > 0)
            output_vel.linear.y = 0.01;

        else if(std::abs(output_vel.linear.y) <= 0.01 && output_vel.linear.y < 0)
            output_vel.linear.y = -0.01;


        if(std::abs(last_x) <= 0.01 && std::abs(last_y) <= 0.01)
            count++;

        //顯示資訊
        std::cout <<"X:"<<location_x<<" Y:"<<location_y<< std::endl;
        std::cout <<"Input-speed_X:"<<vel.linear.x<<" Input-speed_Y:"<<vel.linear.y<< std::endl;
        std::cout <<"Output-speed_X:"<<output_vel.linear.x<<" Output-speed_Y:"<<output_vel.linear.y<< std::endl;
        std::cout <<"target_number:"<<count<< std::endl;
        std::cout <<"----------------------------------------------------------"<< std::endl;

        pub.publish( output_vel);

        loop_rate.sleep();
    }

    output_vel.linear.x = 0;
    output_vel.linear.y = 0;

    pub.publish(output_vel);

    std::cout <<"END"<<std::endl;

    return 0;
} 


//實際程式架構，log
#include "ros/ros.h"
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Point.h>

//最大速度-單位?
#define speed 50

geometry_msgs::Twist vel;

//回傳位置
void Callback(geometry_msgs::Twist input_vel){

    vel.linear.x = input_vel.linear.x;
    vel.linear.y = input_vel.linear.y;
}

int main(int argc, char **argv){

    ros::init(argc, argv, "move2");
    ros::NodeHandle nh;

    ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("$pub_name",1);
    ros::Subscriber sub = nh.subscribe("$sub_name",10,Callback);

    ros::Rate loop_rate(10);

    geometry_msgs::Twist output_vel;
    geometry_msgs::Point target;
    geometry_msgs::Point start;
    
    int count = 1;

    double location_x = 0, location_y = 0;
    
    while(ros::ok() && count <= 5){

        ros::spinOnce();

        switch(count){
            //目標點-單位cm
            case 1:
                target.x = 140;
                target.y = 0;
                start.x = 0;
                start.y = 0;
                break;
            case 2:
                target.x = 140;
                target.y = 47.5;
                start.x = 140;
                start.y = 0;
                break;
            case 3:
                target.x = 250;
                target.y = 47.5;
                start.x = 140;
                start.y = 47.5;
                break;
            case 4:
                target.x = 250;
                target.y = 5;
                start.x = 250;
                start.y = 47.5;
                break;
            case 5:
                target.x = 400;
                target.y = 5;
                start.x = 250;
                start.y = 5;
                break;
            default:
                break;
        }

        //使用速度換算距離-0.1為頻率的倒數，即時間
        location_x += vel.linear.x * 0.1;
        location_y += vel.linear.y * 0.1;
        double last_x = (target.x - location_x), last_y = (target.y - location_y);
        double distance_x = std::abs(target.x - start.x), distance_y = std::abs(target.y - start.y);

        if(target.x == start.x)
            distance_x = 1;

        if(target.y == start.y)
            distance_y = 1;

        //依離目標點的位置減少速度
        if(std::abs(speed * last_x / distance_x) <= 1){

            if(target.x == start.x)//微調
                output_vel.linear.x = speed / 10 * (last_x / distance_x);
            else//0.02為底限速度
                output_vel.linear.x = 0.1;
        }
        else
            output_vel.linear.x = std::log(speed * std::abs(last_x) / distance_x);

        if(std::abs(speed * last_y / distance_y) <= 1){

            if(target.y == start.y)//微調
                output_vel.linear.y = speed  / 10 * (last_y / distance_y);
            else//0.02為底限速度
                output_vel.linear.y = 0.1;
        }
        else
            output_vel.linear.y = std::log(speed * std::abs(last_y) / distance_y);    
        //方向調整
        if(last_x < 0)
            output_vel.linear.x *= -1;

        if(last_y < 0)
            output_vel.linear.y *= -1;

        if(std::abs(last_x) < 0.05 && std::abs(last_y) < 0.05)
            count++;

        //顯示資訊
        std::cout <<"X:"<<location_x<<" Y:"<<location_y<< std::endl;
        std::cout <<"Input-speed_X:"<<vel.linear.x<<" Input-speed_Y:"<<vel.linear.y<< std::endl;
        std::cout <<"Output-speed_X:"<<output_vel.linear.x<<" Output-speed_Y:"<<output_vel.linear.y<< std::endl;
        std::cout <<"target_number:"<<count<< std::endl;
        std::cout <<"----------------------------------------------------------"<< std::endl;

        pub.publish( output_vel);

        loop_rate.sleep();
    }

    output_vel.linear.x = 0;
    output_vel.linear.y = 0;

    pub.publish(output_vel);

    std::cout <<"END"<<std::endl;

    return 0;
}