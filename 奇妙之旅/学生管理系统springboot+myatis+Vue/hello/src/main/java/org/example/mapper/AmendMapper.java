package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.boot.bean.Select;

public interface AmendMapper {
    void reqisterAmend(@Param("select")Select select);
    void reqisterAmend1(@Param("select") Select select);
}
