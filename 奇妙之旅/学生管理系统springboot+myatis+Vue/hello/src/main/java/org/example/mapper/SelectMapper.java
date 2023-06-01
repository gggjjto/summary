package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.boot.bean.Select;

import java.util.List;

public interface SelectMapper {
    Select reqisterselect(@Param("sid")Integer sid);
    List<Select> reqisterSelectAll();
}
