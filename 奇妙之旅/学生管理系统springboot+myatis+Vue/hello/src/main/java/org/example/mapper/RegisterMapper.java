package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.boot.bean.Account;

/**
 * @author hxc
 * @dateTime: 2021-12-2
 * @description: 注册mapper
 * */
public interface RegisterMapper {
    // 注册
    void registerAccount(@Param("account") Account account);
}

