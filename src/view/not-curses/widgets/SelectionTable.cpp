//
// Created by oschdi on 09.10.25.
//

#include "view/not_curses/widgets/SelectionTable.hpp"

SelectionTable::SelectionTable(const uint32_t column_count) : Table(column_count) {

}

void SelectionTable::setActive(const bool is_active) {
    this->active = is_active;
}

void SelectionTable::moveSelectionDown(const uint32_t distance) {
    if (rows.empty())
        return;
    selected_row = std::min(static_cast<uint32_t>(rows.size() - 1), selected_row + distance);
}

void SelectionTable::moveSelectionUp(uint32_t distance) {
    if (rows.empty())
        return;
    selected_row = std::max(0, static_cast<int32_t>(selected_row) - static_cast<int32_t>(distance));
}

std::string SelectionTable::getSelectedKey() {
    return rows.at(selected_row).at(0);
}

void SelectionTable::drawToPlane(const PlaneHandle &plane, const glm::ivec2 pos, const glm::ivec2 table_size) const {
    Table::drawToPlane(plane, pos, table_size);

    if (!active || rows.empty())
        return;
    const uint32_t column_width = std::floor(table_size.x / float(column_count));
    const uint32_t string_max_length = column_width - 1;

    drawRow(plane, pos, selected_row, column_width, string_max_length, SELECTED);
}

bool SelectionTable::isEmpty() const {
    return rows.empty();
}
