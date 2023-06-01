package org.example.boot.config;

import org.example.boot.bean.User;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
public class Myconfig {

    @Bean
    public User user01(){
        return new User("zhangshang",18);
    }
}
