package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.boot.bean.Student;

public interface StudentMapper {
    void registerstudent(@Param("student") Student student);
}
