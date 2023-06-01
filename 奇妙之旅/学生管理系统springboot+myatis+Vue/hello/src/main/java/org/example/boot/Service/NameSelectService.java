package org.example.boot.Service;

import org.example.boot.bean.Select;
import org.example.mapper.NameSelectMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class NameSelectService {
    @Resource
    private NameSelectMapper nameSelectMapper;
    public List<Select> registerNameSelect(String sname){
        //System.out.println(nameSelectMapper.reqisternameselect(sname));
        return nameSelectMapper.reqisternameselect(sname);
    }
}
