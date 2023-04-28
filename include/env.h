/*
 * @Author: 董泰宏 2396203400@qq.com
 * @Date: 2023-04-28 09:29:14
 * @LastEditors: 董泰宏 2396203400@qq.com
 * @LastEditTime: 2023-04-28 16:33:38
 * @FilePath: /QLearningVisualization/include/env.h
 * @Description:
 * Copyright (c) 2023 by 董泰宏 email: 2396203400@qq.com, All Rights Reserved.
 */

#pragma once

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::sort;
using std::vector;

const int map_h = 30;
const int map_w = 30;
const int size_x = 20;
const int size_y = 20;
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define Free 0
#define OBSTACLE 1

/**
 * @description: 存储着强化学习的值表Q-table, 以及行为组合action
 * @return {*}
 */
class Environment {
 public:
  Environment(int map_h_size, int map_w_size) {
    vector<vector<double>> temp_table(map_h_size * map_w_size,
                                      vector<double>(4, 0));
    q_table_ = std::move(temp_table);
    action_ = {UP, DOWN, LEFT, RIGHT};
  }
  ~Environment() = default;
  vector<vector<double>> q_table_;
  vector<int> action_;
};