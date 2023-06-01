package org.example.mapper;

import org.apache.ibatis.annotations.Param;
import org.example.boot.bean.Scores;

public interface ScoresMapper {
    void registerscres(@Param("scores")Scores scores);
}
