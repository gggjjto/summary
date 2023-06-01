package org.example.controller;

import org.example.boot.Service.AmendService;
import org.example.boot.Vo.ResultVo;
import org.example.boot.bean.Select;
import org.example.boot.constant.ResutEnum;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;

@RestController
public class AmendController {
    @Resource
    private AmendService amendService;
    @RequestMapping("/Amend")
    public ResultVo amendTosystem(@RequestParam("sid") Integer sid,@RequestParam("sname") String sname,
                                  @RequestParam("sbirthday") String sbirthday,@RequestParam("sgender")String sgender,
                                  @RequestParam("sclass_id") Integer sclass_id,@RequestParam("javascore")Integer javascore,
                                  @RequestParam("mathscore") Integer mathscore,@RequestParam("englishscore") Integer englishscore,
                                  @RequestParam("sportsscore") Integer sportsscore){
        Select select = new Select(sid,sname,sbirthday,sgender,sclass_id,javascore,mathscore,englishscore,sportsscore);
        System.out.println(select.toString());
        return new ResultVo(ResutEnum.OK,amendService.registerAmend(select));
    }
//    public ResultVo amendTosystem(@RequestBody Select select){
//        //Select select = new Select(sid,sname,sbirthday,sgender,sclass_id,javascore,mathscore,englishscore,sportsscore);
//        return new ResultVo(ResutEnum.OK,amendService.registerAmend(select));
//    }

}
