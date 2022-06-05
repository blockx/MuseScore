/*
 * SPDX-License-Identifier: GPL-3.0-only
 * MuseScore-CLA-applies
 *
 * MuseScore
 * Music Composition & Notation
 *
 * Copyright (C) 2021 MuseScore BVBA and others
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef MU_ENGRAVING_TEMPORANGEDCHANGEANNOTATION_H
#define MU_ENGRAVING_TEMPORANGEDCHANGEANNOTATION_H

#include "chordtextlinebase.h"
#include "types/types.h"

namespace mu::engraving {
class TempoChangeRangedSegment;
class TempoChangeRanged : public ChordTextLineBase
{
public:
    TempoChangeRanged(EngravingItem* parent);

    TempoChangeRanged* clone() const override;

    void read(XmlReader& reader) override;
    void write(XmlWriter& writer) const override;

    LineSegment* createLineSegment(System* parent) override;

    TempoChangeType tempoChangeType() const;
    ChangeMethod easingMethod() const;
    void setTempoChangeType(const TempoChangeType type);

    float tempoChangeFactor() const;

    PropertyValue getProperty(Pid id) const override;
    bool setProperty(Pid id, const PropertyValue& val) override;
    PropertyValue propertyDefault(Pid propertyId) const override;
    Sid getPropertyStyle(Pid id) const override;

protected:
    void added() override;
    void removed() override;

private:
    void requestToRebuildTempo();

    TempoChangeType m_tempoChangeType = TempoChangeType::Undefined;
    ChangeMethod m_tempoEasingMethod = ChangeMethod::NORMAL;

    friend class TempoChangeRangedSegment;
};

class TempoChangeRangedSegment : public TextLineBaseSegment
{
public:
    TempoChangeRangedSegment(TempoChangeRanged* annotation, System* parent);

    TempoChangeRangedSegment* clone() const override;

    TempoChangeRanged* tempoChange() const;

    void layout() override;
    void endEdit(EditData& editData) override;
    void added() override;
    void removed() override;

    friend class TempoChangeRanged;
};
}

#endif // MU_ENGRAVING_TEMPORANGEDCHANGEANNOTATION_H
