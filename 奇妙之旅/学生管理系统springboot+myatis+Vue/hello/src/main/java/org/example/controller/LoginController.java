package org.example.controller;


import org.example.boot.Service.LoginService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
//@RequestMapping("/login/**")
public class LoginController {
    @Resource
    private LoginService loginService;

    // 登录到系统
    @RequestMapping("/loginTosystem")
    public ResultVo loginTosystem(@RequestParam("username")String username, @RequestParam("password")String password) {
        if(loginService.loginTosystem1(username,password)){
            return new ResultVo(ResutEnum.OK,loginService.loginTosystem(username,password));
        }
        else{
            return new ResultVo(ResutEnum.Error,loginService.loginTosystem(username,password));
        }

    }
    @RequestMapping("/findName")
    public ResultVo findName(@RequestParam("id")Integer id) {
        return new ResultVo(ResutEnum.OK,loginService.findName(id));
    }

    @RequestMapping("/hello1")
    public String handle01(){
        return "Hello,Spring boot 2";
    }
}

