package org.example.boot.Service;


import org.example.mapper.LoginMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * @author jp
 * @dateTime: 2023-6-1
 * @description: 登录service
 * */
@Service
public class LoginService {
    @Resource
    private LoginMapper loginMapper;
    // 登录
    public String loginTosystem(String username,String password){
        String message = "";
        // 判断登录的角色是否为空
        if(loginMapper.loginTosystem(username,password)== null) {
            message = "登录失败";
        }else {
            loginMapper.loginTosystem(username,password);
            message = "登录成功";
        }
        return message;
    }
    public boolean loginTosystem1(String username,String password){
        boolean message;
        // 判断登录的角色是否为空
        if(loginMapper.loginTosystem(username,password)== null) {
            message = false;
        }else {
            loginMapper.loginTosystem(username,password);
            message = true;
        }
        return message;
    }

    // 获取登录人员的姓名
    public String findName(Integer id) {
        return loginMapper.findName(id);
    }
}

