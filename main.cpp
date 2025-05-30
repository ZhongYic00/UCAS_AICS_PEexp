#include <verilated.h>
#include <verilated_fst_c.h>
#define VTOP Vtb_top_0
#include "Vtb_top_0.h" // Verilated model header for tb_top_0

#define SIM_TIME 10000 // Simulation time in cycles

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VerilatedContext *m_contextp = new VerilatedContext; // Context
    VerilatedFstC *m_tracep = new VerilatedFstC;         // Trace
    // Instantiate the Verilated model
    VTOP *tb = new VTOP;
    // Trace configuration
    m_contextp->traceEverOn(true);     // Turn on trace switch in context
    tb->trace(m_tracep, 3);        // Set depth to 3
    m_tracep->open("cnt_ceil_wf.fst"); // Open the FST file to store data
    // Write data to the waveform file
    while (!m_contextp->gotFinish())
    {
        // Refresh circuit state
        tb->eval();
        // Dump data
        m_tracep->dump(m_contextp->time());
        // Increase simulation time
        m_contextp->timeInc(1);
    }
    // Remember to close the trace object to save data in the file
    m_tracep->close();
    // Free memory
    delete tb;
    return 0;
}