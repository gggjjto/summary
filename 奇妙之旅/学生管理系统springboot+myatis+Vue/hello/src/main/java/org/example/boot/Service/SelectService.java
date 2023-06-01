package org.example.boot.Service;

import org.example.boot.bean.Select;
import org.example.mapper.SelectMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class SelectService {
    @Resource
    private SelectMapper selectMapper;

    public Select registerSelect(Integer sid){
        return selectMapper.reqisterselect(sid);
    }

    public List<Select> registerSelectAll(){
        return selectMapper.reqisterSelectAll();
    }

}
