#include "Task.hpp"

using namespace tmtc_mock;

Task::Task(std::string const& name)
    : TaskBase(name)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine)
    : TaskBase(name, engine)
{
}

Task::~Task()
{
}

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;
    return true;
}
bool Task::startHook()
{
    if (! TaskBase::startHook())
        return false;
    return true;
}
void Task::updateHook()
{
    TaskBase::updateHook();

    // construct command
    telemetry_telecommand::messages::Telecommand command;
    command.productType = telemetry_telecommand::messages::IMAGE;
    command.productMode = telemetry_telecommand::messages::ONE_SHOT;
    command.usecPeriod = 0;

    // send command
    _telecommand_out.write( command );
}
void Task::errorHook()
{
    TaskBase::errorHook();
}
void Task::stopHook()
{
    TaskBase::stopHook();
}
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
}
