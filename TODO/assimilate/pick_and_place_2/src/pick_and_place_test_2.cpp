
#include <ros/ros.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <iostream>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>

using namespace std;
using namespace geometry_msgs;
using namespace moveit;
using namespace planning_interface;

double tol=0.005;
unsigned int attempt=1000;
static const string PLANNING_GROUP = "almax_arm";
bool success;

MoveGroupInterface *robot;

moveit::planning_interface::MoveGroupInterface::Plan my_plan;
vector<double> joint_group_positions;


//ruota giunto dell'angolo in ingresso
void ruotagiunto(unsigned int giunto,double angolo){


  joint_group_positions=robot->getCurrentJointValues();
  joint_group_positions[giunto] = joint_group_positions[giunto]+(angolo*3.1415/180);  // radians
  robot->setJointValueTarget(joint_group_positions);


  success = (robot->plan(my_plan) == moveit::planning_interface::MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "%s", success ? "SUCCESS" : "FAILED");
  robot->move();

  }
//setta l'angolo all'angolo in ingresso
void set_angolo(unsigned int giunto,double angolo)
{


  joint_group_positions=robot->getCurrentJointValues();
  joint_group_positions[giunto] = (angolo*3.1415)/180;  // radians
  robot->setJointValueTarget(joint_group_positions);


  success = (robot->plan(my_plan) == MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "%s", success ? "SUCCESS" : "FAILED");
  robot->move();
}
//setta Pose
void move_to_pose(geometry_msgs::Pose pt){


  robot->setPoseTarget(pt);

  success = (robot->plan(my_plan) == MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "Provo a muovermi fino a dove mi hai detto tu, Risultato:%s", success ? "SUCCESS" : "FAILED");
  robot->move();
}
//stampa position end effector
void stampa_endeffector(geometry_msgs::Pose po)
{
  cout<<"Position"<<endl<<"X:"<<po.position.x<<endl<<"Y:"<<po.position.y<<endl<<"Z:"<<po.position.z<<endl;
  cout<<endl<<"Orientation"<<endl<<"X:"<<po.orientation.x<<endl<<"Y:"<<po.orientation.y<<endl<<"Z:"<<po.orientation.z<<endl<<"W:"<<po.orientation.w<<endl;
}
//stampa posizione giunti
void stampa_giunti()
{
  joint_group_positions=robot->getCurrentJointValues();
  cout<<endl<<"Giunti:"<<endl;
  for(int i=0;i<joint_group_positions.size();i++){
    cout<<i<<":"<<joint_group_positions[i]<<endl;
  }
}
//setta il robot in full stand
void full_stand(){

  joint_group_positions=robot->getCurrentJointValues();
  for(unsigned int i=0;i<6;i++)
    joint_group_positions[i]=0;
  robot->setJointValueTarget(joint_group_positions);

  success = (robot->plan(my_plan) == MoveItErrorCode::SUCCESS);
  ROS_INFO_NAMED("tutorial", "%s", success ? "SUCCESS" : "FAILED");
  robot->move();
}
//controlla il comando della tastiera
void controlla(string k){

    Pose targ=robot->getCurrentPose().pose;

    unsigned int giunto=0;
    int positivita=1;
    int angolo_base=30;
    bool b_angolo=false,b_move=false;
    double z=0,x=0,y=0;


    //se ho messo un carattere
    if(k.size()==1){
      //se è un numero
      if('1'<=k[0] && k[0]<='6'){
        giunto=k[0]-'1';
        b_angolo=true;
      }
      //full_stand
      if(k[0]=='f'){
        full_stand();
      }
      if(k[0]=='r'){

        cout<<endl<<endl<<"Attuale tolleranza:"<<endl<<tol;
        cout<<endl<<endl<<"Attuali attempts:"<<endl<<attempt;

        cout<<endl<<"Quanto vuoi di tolleranza?"<<endl<<"Tolleranza:";
        cin>>tol;
        cout<<"Quanti tentativi vuoi fargli fare?"<<endl<<"Tentativi:";
        cin>>attempt;
      }
      if(k[0]=='g'){
        stampa_giunti();
      }
      if(k[0]=='e'){
        cout<<endl<<endl<<"Inserisci da 1 a 6 per ruotare il giunto poi clicca invio"<<endl<<"se vuoi che giri dall'altra parte mettici '-' davanti per esempio: '-1' poi invio farà muovere il primo giunto di un angolo negativo"<<endl;
        cout<<"Inserisci f per mandarlo in posizione originale"<<endl;
        cout<<"inserisci x o y o z poi clicca invio per farlo muovere nella corrispettiva direzione"<<endl;
        cout<<" '-x + enter' lo fa andare in direzione x opposta"<<endl;
        cout<<" 'r' resetta tolleranza e attempt"<<endl;
      }
      //aumento x
      if(k[0]=='x'){
        b_move=true;
        x+=0.2;
      }
      //aumento y
      if(k[0]=='y'){
        b_move=true;
        y+=0.2;
      }
      //aumento z
      if(k[0]=='z'){
        b_move=true;
        z+=0.2;
      }

//      if(k[0]=='s'){
//        int n;
//        string t;
//        std::vector<geometry_msgs::Pose> waypoints;
//        waypoints.push_back(targ);
//        cout<<endl<<endl<<"Quante successioni vuoi mettere:";
//        cin>>n;
//        for(int i=0;i<n;i++){
//          cout<<"Inserisci il "<<i<<":";
//          cin>>t;
//          if(t.size()==1){
//            //aumento x
//            if(t[0]=='x'){
//              b_move=true;
//              x+=0.2;
//            }
//            //aumento y
//            if(t[0]=='y'){
//              b_move=true;
//              y+=0.2;
//            }
//            //aumento z
//            if(t[0]=='z'){
//              b_move=true;
//              z+=0.2;
//            }
//          }
//         if(t.size()==2){
//           if(t[0]=='-'){
//             positivita=-1;
//           }
//           if(t[1]=='x'){
//             b_move=true;
//             x+=0.2;
//           }
//           if(t[1]=='y'){
//             b_move=true;
//             y+=0.2;
//           }
//           if(t[1]=='z'){
//             b_move=true;
//             z+=0.2;
//           }
//        }

//      }
//        if(b_move){
//          targ.position.x+=x*positivita;
//          targ.position.y+=y*positivita;
//          targ.position.z+=z*positivita;
//          waypoints.push_back(targ);
//          move_group.setMaxVelocityScalingFactor(0.1);//questo poi va resettato a default!!!
//          moveit_msgs::RobotTrajectory trajectory;
//          const double jump_threshold = 0.0;
//          const double eef_step = 0.01;
//          double fraction = move_group.computeCartesianPath(waypoints, eef_step, jump_threshold, trajectory);
//          ROS_INFO_NAMED("tutorial", "Visualizing plan 4 (Cartesian path) (%.2f%% acheived)", fraction * 100.0);
//        }
//      }
}
    if(k.size()==2){
      if(k[0]=='-'){
        positivita=-1;
      }
      if('1'<=k[1] && k[1]<='6'){
        giunto=k[1]-'1';
        b_angolo=true;
      }
      if(k[1]=='x'){
        b_move=true;
        x+=0.2;
      }
      if(k[1]=='y'){
        b_move=true;
        y+=0.2;
      }
      if(k[1]=='z'){
        b_move=true;
        z+=0.2;
      }

    }



    if(b_angolo){
      ruotagiunto(giunto,positivita*angolo_base);
    }
    else{
      if(b_move){

        targ.position.x+=x*positivita;
        targ.position.y+=y*positivita;
        targ.position.z+=z*positivita;
        move_to_pose(targ);

      }
    }
}



//ricorda che hai messo prmstar come risolutore cinematico


int main(int argc, char** argv)
{


  ros::init(argc, argv, "almax_arm_pick_and_place");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  ros::WallDuration(1.0).sleep();
  MoveGroupInterface move_group(PLANNING_GROUP);
  robot=&move_group;
  namespace rvt = rviz_visual_tools;

  string comando;
  cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
  do{
      cout<<endl<<endl<<endl;
      cout<<endl<<"p)Esci"<<endl<<"e)Guida"<<endl<<"Tasto:";
      cin>>comando;
      controlla(comando);
  }while(comando!="p");



  ros::shutdown();
  return 0;

}
