package org.example.controller;


import org.example.boot.Service.RegisterService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.bean.Account;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;


@RestController
@RequestMapping("/register/**")
public class RegisterController {
    @Resource
    private RegisterService registerService;

    // 注册
    @PostMapping("/registerAccount")
    public ResultVo registerAccount(@RequestBody Account account) {
        return new ResultVo(ResutEnum.OK,registerService.registerAccount(account));
    }
}
