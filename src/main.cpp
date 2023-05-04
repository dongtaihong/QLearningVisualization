/*
 * @Author: 董泰宏 2396203400@qq.com
 * @Date: 2023-04-28 09:29:48
 * @LastEditors: 董泰宏 2396203400@qq.com
 * @LastEditTime: 2023-05-04 15:27:28
 * @FilePath: /QLearningVisualization/src/main.cpp
 * @Description: 使用Q-Learning进行网格地图路径规划
 * Copyright (c) 2023 by 董泰宏 email: 2396203400@qq.com, All Rights Reserved.
 */
#include "Qlearning.h"

int main(int argv, char* argc[]) {
  //初始化网格地图、起点终点、障碍物
  GridMap(0, 0, map_w - 1, map_h - 1);

  //初始化环境
  Environment myenv(map_h, map_w);

  //在当前环境进行训练
  QLearning rl(myenv, 3500, 0.1, 0.9, 0.1, map_h - 1, map_w - 1);

  //打印网格图
  PrintFinalPath(rl);
  return 0;
}