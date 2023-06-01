package org.example.controller;


import org.example.boot.Service.SelectService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.bean.Select;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

@RestController
public class SelectController {
    @Resource
    private SelectService selectService;

    @RequestMapping("/select")
    public ResultVo registerSelect(@RequestParam("sid") Integer sid){
        Select select=selectService.registerSelect(sid);
        System.out.println(select.toString());
        return new ResultVo(ResutEnum.OK,select);
    }

    @RequestMapping("/allSelect")
    public ResultVo registerSelectAll(){
        return new ResultVo(ResutEnum.OK,selectService.registerSelectAll());
    }
}
