#ifndef EXOSPHERE_FLOW_CTLR_H
#define EXOSPHERE_FLOW_CTLR_H

#include <stdint.h>
#include "cpu_context.h"
#include "memory_map.h"

/* Exosphere register definitions for the Tegra X1 Flow Controller. */

static inline uintptr_t get_flow_base(void) {
    return MMIO_GET_DEVICE_ADDRESS(MMIO_DEVID_FLOWCTRL);
}

#define FLOW_BASE (get_flow_base())

#define MAKE_FLOW_REG(ofs) (*((volatile uint32_t *)(FLOW_BASE + ofs)))

#define FLOW_CTLR_HALT_COP_EVENTS_0 MAKE_FLOW_REG(0x004)
#define FLOW_CTLR_L2FLUSH_CONTROL_0 MAKE_FLOW_REG(0x094)


static const struct {
    unsigned int CPUN_CSR_OFS;
    unsigned int HALT_CPUN_EVENTS_OFS;
    unsigned int CC4_COREN_CTRL_OFS;
} g_flow_core_offsets[NUM_CPU_CORES] = {
    {0x008, 0x000, 0x06C},
    {0x018, 0x014, 0x070},
    {0x020, 0x01C, 0x074},
    {0x028, 0x024, 0x078},
};

static inline void flow_set_cc4_ctrl(uint32_t core, uint32_t cc4_ctrl) {
    MAKE_FLOW_REG(g_flow_core_offsets[core].CC4_COREN_CTRL_OFS) = cc4_ctrl;
}

static inline void flow_set_halt_events(uint32_t core, uint32_t halt_events) {
    MAKE_FLOW_REG(g_flow_core_offsets[core].HALT_CPUN_EVENTS_OFS) = halt_events;
}

static inline void flow_set_csr(uint32_t core, uint32_t csr) {
    MAKE_FLOW_REG(g_flow_core_offsets[core].CPUN_CSR_OFS) = csr;
}

static inline void flow_clear_csr0_and_events(uint32_t core) {
    MAKE_FLOW_REG(g_flow_core_offsets[core].CPUN_CSR_OFS) = 0;
    MAKE_FLOW_REG(g_flow_core_offsets[core].HALT_CPUN_EVENTS_OFS) = 0;
}

#endif
