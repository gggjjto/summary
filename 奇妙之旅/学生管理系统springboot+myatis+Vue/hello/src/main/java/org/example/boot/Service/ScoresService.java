package org.example.boot.Service;

import org.example.boot.bean.Scores;
import org.example.mapper.ScoresMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class ScoresService {
    @Resource
    private ScoresMapper scoresMapper;


    public String registerScores(Scores scores){
        scoresMapper.registerscres(scores);
        return "注册成功";
    }
}
