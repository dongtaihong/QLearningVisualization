/*
 * @Author: 董泰宏 2396203400@qq.com
 * @Date: 2023-04-28 09:29:41
 * @LastEditors: 董泰宏 2396203400@qq.com
 * @LastEditTime: 2023-04-28 16:44:22
 * @FilePath: /QLearningVisualization/src/Qlearning.cpp
 * @Description:
 * Copyright (c) 2023 by 董泰宏 email: 2396203400@qq.com, All Rights Reserved.
 */
#include "Qlearning.h"

#include "env.h"
vector<vector<int>> map = vector<vector<int>>(map_h, vector<int>(map_w, 0));
cv::Mat visualMap(map_h* size_y, map_w* size_x, CV_8UC3,
                  cv::Scalar(255, 255, 255));

void GridMap(double start_x, double start_y, double end_x, double end_y) {
  // 绘制水平方向的网格线
  for (int r = 0; r <= map_w; r++) {
    cv::Point p1(0, r * size_y);
    cv::Point p2(map_w * size_x, r * size_y);
    cv::line(visualMap, p1, p2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
  }

  // 绘制垂直方向的网格线
  for (int c = 0; c <= map_h; c++) {
    cv::Point p1(c * size_x, 0);
    cv::Point p2(c * size_x, map_h * size_y);
    cv::line(visualMap, p1, p2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
  }

  //起点、终点
  cv::rectangle(visualMap,
                cv::Rect(start_x * size_x, start_y * size_y, size_x, size_y),
                cv::Scalar(0, 0, 255), -1);
  cv::rectangle(visualMap,
                cv::Rect(end_x * size_x, end_y * size_y, size_x, size_y),
                cv::Scalar(0, 0, 255), -1);

  //障碍物
  for (int i = 4; i < 8; i++) {
    cv::rectangle(visualMap, cv::Rect(i * size_x, 20 * size_y, size_x, size_y),
                  cv::Scalar(0, 0, 0), -1);
    map[i][20] = 1;
  }
  //   for (int i = 24; i < 30; i++) {
  //     cv::rectangle(visualMap, cv::Rect(i * size_x, 22 * size_y, size_x,
  //     size_y),
  //                   cv::Scalar(0, 0, 0), -1);
  //     map[i][22] = 1;
  //   }
  for (int i = 14; i < 28; i++) {
    cv::rectangle(visualMap, cv::Rect(i * size_x, 10 * size_y, size_x, size_y),
                  cv::Scalar(0, 0, 0), -1);
    map[i][10] = 1;
  }
  for (int i = 4; i < 30; i++) {
    cv::rectangle(visualMap, cv::Rect(25 * size_x, i * size_y, size_x, size_y),
                  cv::Scalar(0, 0, 0), -1);
    map[25][i] = 1;
  }
}

int chooseAction(const std::vector<double>& probabilities) {
  // 定义一个连续分布随机数生成器
  std::random_device rd;
  std::mt19937 gen(rd());
  std::discrete_distribution<> dis(probabilities.begin(), probabilities.end());

  // 生成一个随机数作为索引，返回被选择的行为
  return dis(gen);
}

/**
 * @description: 根据当前的位置选择下一步的动作
 * @param {vector<int>} position
 * @return {*}
 */
int QLearning::EGreedy(Environment& env, vector<int> position) {
  //当前最优行为
  int flag = 0;
  double reward_flag = -10000;
  for (int i = 0; i < 4; i++) {
    if (env.q_table_[position[0] * map_w + position[1]][i] > reward_flag) {
      reward_flag = env.q_table_[position[0] * map_w + position[1]][i];
      flag = i;
    }
  }
  //各行为的概率值
  int action_optimal = flag;
  vector<double> prob(4, 0);
  for (int i = 0; i < 4; i++) {
    prob[i] = double(epsilon_ / double(3.0));
    if (i == flag) {
      prob[i] = 1 - epsilon_;
    }
  }
  if (position[0] == 0) {
    prob[UP] = 0;
  }
  if (position[0] == map_h - 1) {
    prob[DOWN] = 0;
  }
  if (position[1] == 0) {
    prob[LEFT] = 0;
  }
  if (position[1] == map_w - 1) {
    prob[RIGHT] = 0;
  }

  //根据当前概率分布选择相应的行为
  int action_probb = chooseAction(prob);
  return action_probb;
}

vector<int> QLearning::step(Environment& env, int& action, double& reward,
                            int end_x, int end_y) {
  if (action == UP) {
    reward = -10;
    if (map[position[0] - 1][position[1]] == 1) {
      reward = UNREACHABLE;
    }
    if (position[0] - 1 == end_x && position[1] == end_y) reward = 10000;
    return vector<int>{position[0] - 1, position[1]};
  } else if (action == DOWN) {
    reward = -10;
    if (map[position[0] + 1][position[1]] == 1) {
      reward = UNREACHABLE;
    }
    if (position[0] + 1 == end_x && position[1] == end_y) reward = 10000;
    return vector<int>{position[0] + 1, position[1]};
  } else if (action == LEFT) {
    reward = -10;
    if (map[position[0]][position[1] - 1] == 1) {
      reward = UNREACHABLE;
    }
    if (position[0] == end_x && position[1] - 1 == end_y) reward = 10000;
    return vector<int>{position[0], position[1] - 1};
  } else {
    reward = -10;
    if (map[position[0]][position[1] + 1] == 1) {
      reward = UNREACHABLE;
    }
    if (position[0] == end_x && position[1] + 1 == end_y) reward = 10000;
    return vector<int>{position[0], position[1] + 1};
  }
  cout << "can not move" << endl;
  return vector<int>{};
}

QLearning::QLearning(Environment& env, int episodes, double alpha, double gamma,
                     double epsilon, int end_x, int end_y)
    : episodes_(episodes), alpha_(alpha), gamma_(gamma), epsilon_(epsilon) {
  //初始化边界
  for (int i = 0; i < map_h; i++) {
    for (int j = 0; j < map_w; j++) {
      if (i == 0)
        env.q_table_[i * map_w + j][0] = UNREACHABLE;  //第一行不能往上走
      if (i == (map_h - 1))
        env.q_table_[i * map_w + j][1] = UNREACHABLE;  //最后一行不能往下走
      if (j == 0)
        env.q_table_[i * map_w + j][2] = UNREACHABLE;  //第一列不能往左走
      if (j == (map_w - 1))
        env.q_table_[i * map_w + j][3] = UNREACHABLE;  //最后一列不能往右走
    }
  }
  int action_prob = 0;
  for (int i = 0; i < episodes; i++) {
    //回到原点
    position[0] = 0;
    position[1] = 0;
    vector<double> final_x;
    vector<double> final_y;
    final_x.push_back(position[0]);
    final_y.push_back(position[1]);
    while (true) {
      action_prob = EGreedy(env, position);  //选择的行为

      double reward = 0;
      vector<int> position_next =
          step(env, action_prob, reward, end_x, end_y);  //根据行为走到下一步

      vector<double> temp_Q =
          env.q_table_[position_next[0] * map_w + position_next[1]];
      sort(temp_Q.begin(), temp_Q.end());  //升序排列
      double Q_max = temp_Q[3];
      env.q_table_[position[0] * map_w + position[1]][action_prob] +=
          alpha * (reward + gamma * Q_max -
                   env.q_table_[position[0] * map_w + position[1]]
                               [action_prob]);  //更新Q-table

      if (position[0] == end_x && position[1] == end_y) break;
      position = std::move(position_next);
      final_x.push_back(position[0]);
      final_y.push_back(position[1]);
    }
    // if (i == episodes - 1) {
    //   for (int w = 0; w < final_x.size(); w++) {
    //     cout << "(" << final_x[w] << ", " << final_y[w] << ") "
    //          << "->";
    //   }
    //   cout << final_x.size() << endl;
    // }
  }
  result_q_table_ = env.q_table_;
}
