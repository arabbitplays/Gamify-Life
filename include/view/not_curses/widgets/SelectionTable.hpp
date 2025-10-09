//
// Created by oschdi on 09.10.25.
//

#ifndef GAMIFY_LIFE_SELECTIONTABLE_HPP
#define GAMIFY_LIFE_SELECTIONTABLE_HPP
#include "Table.hpp"

class SelectionTable;
typedef std::shared_ptr<SelectionTable> SelectionTableHandle;

class SelectionTable : public Table {
public:
    SelectionTable(uint32_t column_count);

    void setActive(bool is_active);

    void moveSelectionDown(uint32_t distance = 1);
    void moveSelectionUp(uint32_t distance = 1);

    std::string getSelectedKey();

    void drawToPlane(const PlaneHandle &plane, glm::ivec2 pos, const glm::ivec2 table_size) const override;

    bool isEmpty() const;

private:
    uint32_t selected_row = 0;
    bool active = false;
};


#endif //GAMIFY_LIFE_SELECTIONTABLE_HPP