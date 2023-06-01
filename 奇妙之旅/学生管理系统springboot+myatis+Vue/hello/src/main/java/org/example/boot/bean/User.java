package org.example.boot.bean;

public class User {
    private String name;
    private Integer age;

    public User(){

    }
    public User(String name,Integer age){
        this.name=name;
        this.age=age;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public Integer getAge() {
        return age;
    }

    @Override
    public String toString(){
        return "name="+name+" ,age="+age;
    }
}
