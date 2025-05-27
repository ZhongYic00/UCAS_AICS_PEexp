#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vtb_top_2.h" // Verilated model header for tb_top_0

#define SIM_TIME 10000 // Simulation time in cycles

int main(int argc, char **argv) {
    Verilated::commandArgs(argc, argv);
    VerilatedContext *m_contextp = new VerilatedContext; // Context
    // VerilatedVcdC *m_tracep = new VerilatedVcdC;         // Trace
    // Instantiate the Verilated model
    Vtb_top_2 *tb = new Vtb_top_2;
    // Trace configuration
    m_contextp->traceEverOn(true);     // Turn on trace switch in context
    // tb->trace(m_tracep, 3);        // Set depth to 3
    // m_tracep->open("cnt_ceil_wf.vcd"); // Open the VCD file to store data
    // Write data to the waveform file
    while (!m_contextp->gotFinish())
    {
        // Refresh circuit state
        tb->eval();
        // Dump data
        // m_tracep->dump(m_contextp->time());
        // Increase simulation time
        m_contextp->timeInc(1);
    }
    // Remember to close the trace object to save data in the file
    // m_tracep->close();
    // Free memory
    delete tb;
    return 0;

    // // Enable waveform dump (optional)
    // // VerilatedVcdC *tfp = nullptr;
    // // Verilated::traceEverOn(true);
    // // tfp = new VerilatedVcdC;
    // // tb->trace(tfp, 99);
    // // tfp->open("waveform.vcd");

    // // Simulation loop
    // vluint64_t sim_time = 0;
    // while (sim_time < SIM_TIME) {
    //     // Toggle clock
    //     tb->clk = sim_time % 2;

    //     // Evaluate the model
    //     tb->eval();

    //     // Dump waveform
    //     // if (tfp) tfp->dump(sim_time);

    //     // Increment simulation time
    //     sim_time++;
    // }

    // // Finalize
    // tb->final();
    // // if (tfp) tfp->close();
    // delete tb;
    // return 0;
}