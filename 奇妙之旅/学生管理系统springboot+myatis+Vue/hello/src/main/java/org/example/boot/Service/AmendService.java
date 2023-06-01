package org.example.boot.Service;

import org.example.boot.bean.Select;
import org.example.mapper.AmendMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class AmendService {
    @Resource
    private AmendMapper amendMapper;

    public String registerAmend(Select select){
        amendMapper.reqisterAmend(select);
        amendMapper.reqisterAmend1(select);
        return "修改成功";
    }

}
