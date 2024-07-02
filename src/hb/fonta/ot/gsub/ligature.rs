use crate::hb::ot_layout_gsubgpos::OT::hb_ot_apply_context_t;
use crate::hb::ot_layout_gsubgpos::{
    ligate_input, match_glyph, match_input, Apply, WouldApply, WouldApplyContext,
};
use skrifa::raw::tables::gsub::{Ligature, LigatureSet, LigatureSubstFormat1};
use ttf_parser::GlyphId;

impl WouldApply for Ligature<'_> {
    fn would_apply(&self, ctx: &WouldApplyContext) -> bool {
        let components = self.component_glyph_ids();
        ctx.glyphs.len() == components.len() + 1
            && components
                .into_iter()
                .map(|comp| GlyphId(comp.get().to_u16()))
                .enumerate()
                .all(|(i, comp)| ctx.glyphs[i + 1] == comp)
    }
}

impl Apply for Ligature<'_> {
    fn apply(&self, ctx: &mut hb_ot_apply_context_t) -> Option<()> {
        // Special-case to make it in-place and not consider this
        // as a "ligated" substitution.
        let components = self.component_glyph_ids();
        if components.is_empty() {
            ctx.replace_glyph(GlyphId(self.ligature_glyph().to_u16()));
            Some(())
        } else {
            let f = |glyph, index| {
                let value = GlyphId(components.get(index as usize).unwrap().get().to_u16());
                match_glyph(glyph, value.0)
            };

            let mut match_end = 0;
            let mut match_positions = smallvec::SmallVec::from_elem(0, 4);
            let mut total_component_count = 0;

            if !match_input(
                ctx,
                components.len() as u16,
                &f,
                &mut match_end,
                &mut match_positions,
                Some(&mut total_component_count),
            ) {
                ctx.buffer
                    .unsafe_to_concat(Some(ctx.buffer.idx), Some(match_end));
                return None;
            }
            let count = usize::from(components.len()) + 1;
            ligate_input(
                ctx,
                count,
                &match_positions,
                match_end,
                total_component_count,
                GlyphId(self.ligature_glyph().to_u16()),
            );
            return Some(());
        }
    }
}

impl WouldApply for LigatureSet<'_> {
    fn would_apply(&self, ctx: &WouldApplyContext) -> bool {
        self.ligatures()
            .iter()
            .filter_map(|lig| lig.ok())
            .any(|lig| lig.would_apply(ctx))
    }
}

impl Apply for LigatureSet<'_> {
    fn apply(&self, ctx: &mut hb_ot_apply_context_t) -> Option<()> {
        for lig in self.ligatures().iter().filter_map(|lig| lig.ok()) {
            if lig.apply(ctx).is_some() {
                return Some(());
            }
        }
        None
    }
}

impl WouldApply for LigatureSubstFormat1<'_> {
    fn would_apply(&self, ctx: &WouldApplyContext) -> bool {
        self.coverage()
            .ok()
            .and_then(|coverage| coverage.get(skrifa::GlyphId::from(ctx.glyphs[0].0)))
            .and_then(|index| self.ligature_sets().get(index as usize).ok())
            .map_or(false, |set| set.would_apply(ctx))
    }
}

impl Apply for LigatureSubstFormat1<'_> {
    fn apply(&self, ctx: &mut hb_ot_apply_context_t) -> Option<()> {
        let glyph = ctx.buffer.cur(0).as_glyph();
        self.coverage()
            .ok()
            .and_then(|coverage| coverage.get(skrifa::GlyphId::from(glyph.0)))
            .and_then(|index| self.ligature_sets().get(index as usize).ok())
            .and_then(|set| set.apply(ctx))
    }
}
