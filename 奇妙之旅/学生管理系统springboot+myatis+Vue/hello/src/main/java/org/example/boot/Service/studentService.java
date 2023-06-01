package org.example.boot.Service;

import org.example.boot.bean.Student;
import org.example.mapper.StudentMapper;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

@Service
public class studentService {
    @Resource
    private StudentMapper studentMapper;

    public Integer registerStudent(Student student){
        studentMapper.registerstudent(student);
        return student.getSid();
    }
}
