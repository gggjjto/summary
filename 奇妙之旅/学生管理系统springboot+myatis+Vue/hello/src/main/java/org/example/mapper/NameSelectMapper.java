package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.boot.bean.Select;

import java.util.List;

public interface NameSelectMapper {
    List<Select> reqisternameselect(@Param("sname")String sname);
}
