package org.example.controller;

import org.example.boot.Service.NameSelectService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
public class NameSelectController {
    @Resource
    private NameSelectService nameSelectService;

    @RequestMapping("/NameSelect")
    public ResultVo registerNameSelect(@RequestParam("sname") String sname1){
        String sname="%"+sname1+"%";
        System.out.println(sname);
        return new ResultVo(ResutEnum.OK,nameSelectService.registerNameSelect(sname));
    }
}
