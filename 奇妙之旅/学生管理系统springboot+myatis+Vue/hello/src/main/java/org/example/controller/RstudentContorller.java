package org.example.controller;


import org.example.boot.Service.studentService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.bean.Student;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
public class RstudentContorller {
    static int[] arr=new int[10];
    @Resource
    private studentService service;

    @RequestMapping("/student_1")
    public ResultVo rstudentContorller(@RequestBody Student student){
        Integer class_id=student.getSclass_id();
        String data=student.getSbirthday();
        data=data.substring(2,4);
        System.out.println(data);
        Integer sid=Integer.parseInt(data);
        sid*=100;
        sid+=class_id;
        sid*=100;
        sid+=(++arr[class_id]);
        student.setSid(sid);
        System.out.println(sid);
        return new ResultVo(ResutEnum.OK,service.registerStudent(student));
    }

    @RequestMapping("/ss")
    public String ss(){
        return "hello";
    }
}
