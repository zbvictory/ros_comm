#include "ros/time.h"
#include "rosbag/bag.h"
#include "rosbag/view.h"
#include "std_msgs/String.h"

#include "boost/foreach.hpp"
#include <gtest/gtest.h>

TEST(rosbag_storage, view_reduce_overlay)
{
  rosbag::Bag bagw;
  bagw.open("/tmp/view_reduce_overlay.bag", rosbag::bagmode::Write);
  std_msgs::String m;
  m.data = "test";
  bagw.write("test_topic", ros::Time::now(), m);
  bagw.close();

  rosbag::Bag bagr;
  bagr.open("/tmp/view_reduce_overlay.bag", rosbag::bagmode::Read);
  rosbag::View v(true);
  v.addQuery(bagr);
  BOOST_FOREACH(rosbag::MessageInstance const m, v) {
    std::cout << "message! " << &m << std::endl;
  }
}

int main(int argc, char **argv) {
    ros::Time::init();

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
