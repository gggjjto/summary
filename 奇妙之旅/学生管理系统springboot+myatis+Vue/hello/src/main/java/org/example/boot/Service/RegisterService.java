package org.example.boot.Service;


import org.example.boot.bean.Account;
import org.example.mapper.RegisterMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class RegisterService {
    @Resource
    private RegisterMapper registerMapper;

    // 注册
    public String registerAccount(Account account) {
        registerMapper.registerAccount(account);
        return "注册成功";
    }
}

