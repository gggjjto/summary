package org.example.mapper;

import org.apache.ibatis.annotations.Param;

public interface LoginMapper {
    // 登录
    String loginTosystem(@Param("username")String username, @Param("password")String password);
    // 获取登录的人的姓名
    String findName(@Param("id")Integer id);
}

