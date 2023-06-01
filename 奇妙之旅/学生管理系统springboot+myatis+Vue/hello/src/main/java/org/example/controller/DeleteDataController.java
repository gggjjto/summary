package org.example.controller;

import org.example.boot.Service.DeleteDataService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
public class DeleteDataController {
    @Resource
    private DeleteDataService deleteDataService;

    @RequestMapping("/DeleteData")
    public ResultVo deleteTosystem(@RequestParam("sid") Integer sid){
        return new ResultVo(ResutEnum.OK,deleteDataService.registerDeleteData(sid));
    }

}
