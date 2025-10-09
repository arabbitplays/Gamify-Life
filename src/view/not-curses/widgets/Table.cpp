//
// Created by oschdi on 09.10.25.
//

#include "view/not_curses/widgets/Table.hpp"

Table::Table(uint32_t column_count) : column_count(column_count) {
}

void Table::addHeader(const Row &row) {
    assert(row.size() == column_count);
    header_row = row;
}

void Table::addRow(const Row &row) {
    assert(row.size() == column_count);
    rows.push_back(row);
}

std::string trimToLength(const std::string& input, std::size_t maxLen) {
    if (input.size() <= maxLen)
        return input; // already short enough
    return input.substr(0, maxLen);
}

void Table::drawToPlane(const PlaneHandle &plane, const glm::ivec2 pos, const glm::ivec2 table_size) const {
    const uint32_t column_width = std::floor(table_size.x / float(column_count));
    const uint32_t string_max_length = column_width - 1;

    for (uint32_t i = 0; i < column_count; i++) {
        std::string trimmed_string = trimToLength(header_row.at(i), string_max_length);
        plane->writeText(glm::ivec2(pos.x + i * column_width, pos.y), trimmed_string, DEFAULT, BOLD);
    }

    for (uint32_t i = 0; i < rows.size(); i++) {
        drawRow(plane, pos, i, column_width, string_max_length);
    }
}

void Table::clear() {
    rows.clear();
}

void Table::drawRow(const PlaneHandle& plane, glm::ivec2 table_pos, uint32_t row_index, uint32_t column_width, uint32_t string_max_length, Color color) const {
    for (uint32_t j = 0; j < column_count; j++) {
        std::string trimmed_string = trimToLength(rows.at(row_index).at(j), string_max_length);
        plane->writeText(glm::ivec2(table_pos.x + j * column_width, table_pos.y + row_index + 1), trimmed_string, color);
    }
}


