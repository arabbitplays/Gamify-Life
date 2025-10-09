//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_TABLE_HPP
#define GAMIFY_LIFE_TABLE_HPP
#include <string>
#include <vector>

#include "view/not_curses/NotCursesPlane.hpp"

class Table;
typedef std::shared_ptr<Table> TableHandle;
typedef std::vector<std::string> Row;

class Table {
public:
    explicit Table(uint32_t column_count);

    void addHeader(const Row& row);
    void addRow(const Row &row);
    virtual void drawToPlane(const PlaneHandle& plane, glm::ivec2 pos, const glm::ivec2 table_size) const;
    void clear();

protected:
    void drawRow(const PlaneHandle& plane, glm::ivec2 table_pos, uint32_t row_index, uint32_t column_width, uint32_t string_max_length, Color color = DEFAULT) const;

    uint32_t column_count;
    Row header_row;
    std::vector<Row> rows;
};


#endif //GAMIFY_LIFE_TABLE_HPP