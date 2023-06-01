package org.example.boot.Service;

import org.example.mapper.DeleteDataMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class DeleteDataService {
    @Resource
    DeleteDataMapper deleteDataMapper;

    public String registerDeleteData(Integer sid){
        deleteDataMapper.reqisterDelete(sid);
        deleteDataMapper.reqisterDelete1(sid);
        return "删除成功";
    }
}
