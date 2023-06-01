package org.example.boot.bean;

import lombok.Data;
import lombok.Getter;
import lombok.Value;

@Data
@Getter
@Value
public class Select {
    private Integer sid;
    private String sname;
    private String sbirthday;
    private String sgender;
    private Integer sclass_id;
    private Integer javascore;
    private Integer mathscore;
    private Integer englishscore;
    private Integer sportsscore;
}
