/*
 * @Author: 董泰宏 2396203400@qq.com
 * @Date: 2023-04-28 09:29:48
 * @LastEditors: 董泰宏 2396203400@qq.com
 * @LastEditTime: 2023-04-28 16:44:43
 * @FilePath: /QLearningVisualization/src/main.cpp
 * @Description:
 * Copyright (c) 2023 by 董泰宏 email: 2396203400@qq.com, All Rights Reserved.
 */

#include "Qlearning.h"

int main(int argv, char* argc[]) {
  GridMap(0, 0, map_w - 1, map_h - 1);
  Environment myenv(map_h, map_w);
  QLearning rl(myenv, 3500, 0.1, 0.9, 0.1, map_h - 1, map_w - 1);

  int point_x = 0;
  int point_y = 0;
  int Num = 1;
  //打印结果
  while (point_x != (map_h - 1) || point_y != (map_w - 1)) {
    cout << "(" << point_x << ", " << point_y << ") "
         << "->";
    if (map[point_x][point_y] == 1) {
      cout << "crush obstacle" << endl;
    }
    cv::rectangle(visualMap,
                  cv::Rect(point_x * size_x, point_y * size_y, size_x, size_y),
                  cv::Scalar(0, 0, 255), -1);

    int flag = 0;
    double reward_flag = UNREACHABLE;
    for (int i = 0; i < 4; i++) {
      if (rl.result_q_table_[point_x * map_w + point_y][i] > reward_flag) {
        reward_flag = rl.result_q_table_[point_x * map_w + point_y][i];
        flag = i;
      }
    }
    if (flag == 0) point_x = point_x - 1;
    if (flag == 1) point_x = point_x + 1;
    if (flag == 2) point_y = point_y - 1;
    if (flag == 3) point_y = point_y + 1;
    Num++;
    if (Num > 1000) {
      cout << "failed" << endl;
      break;
    }
  }
  cout << "(" << point_x << ", " << point_y << ") " << endl;
  cout << Num << endl;

  cv::imshow("QLearning", visualMap);
  cv::waitKey(180000);
  return 0;
}