/*
 * @Author: 董泰宏 2396203400@qq.com
 * @Date: 2023-04-28 09:29:31
 * @LastEditors: 董泰宏 2396203400@qq.com
 * @LastEditTime: 2023-04-28 16:35:05
 * @FilePath: /QLearningVisualization/include/Qlearning.h
 * @Description:
 * Copyright (c) 2023 by 董泰宏 email: 2396203400@qq.com, All Rights Reserved.
 */
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <random>

#include "env.h"

#define UNREACHABLE -10000
extern vector<vector<int>> map;
extern cv::Mat visualMap;

void GridMap(double start_x, double start_y, double end_x, double end_y);
class QLearning {
 public:
  QLearning(Environment& env, int episodes, double alpha, double gamma,
            double epsilon, int end_x, int end_y);
  ~QLearning() = default;
  int EGreedy(Environment& env, vector<int> position);  // e-greedy选择行动
  vector<int> step(Environment& env, int& action, double& reward, int end_x,
                   int end_y);  //进行一步训练
  vector<vector<double>> result_q_table_;

 private:
  int episodes_;
  double alpha_;
  double gamma_;
  double epsilon_;
  vector<int> position{0, 0};
};