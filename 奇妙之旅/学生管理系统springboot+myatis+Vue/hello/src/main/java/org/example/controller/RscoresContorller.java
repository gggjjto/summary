package org.example.controller;


import org.example.boot.Service.ScoresService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.bean.Scores;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
public class RscoresContorller {
    @Resource
    private ScoresService scoresService;

    @RequestMapping("/score")
    public ResultVo rscoresContorller(@RequestBody Scores scores){
        return new ResultVo(ResutEnum.OK,scoresService.registerScores(scores));
    }

    @RequestMapping("/s1")
    public String s1(){
        return "hello";
    }
}
