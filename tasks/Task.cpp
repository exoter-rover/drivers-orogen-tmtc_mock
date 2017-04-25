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
    lastTime = base::Time::now();
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

    // one shot
    base::Time curTime = base::Time::now();
    int64_t elapsedTime = curTime.toMicroseconds() - lastTime.toMicroseconds();
    if (elapsedTime > 5e6)
    {
        lastTime = curTime;
        std::cout << " one shot time " << std::endl;
        //command.productType = telemetry_telecommand::messages::DEM;
        //command.productType = telemetry_telecommand::messages::POINT_CLOUD;
        command.productType = telemetry_telecommand::messages::DISTANCE;
        //command.productType = telemetry_telecommand::messages::IMAGE;
        command.productMode = telemetry_telecommand::messages::ONE_SHOT;

        // send command
        _telecommand_out.write( command );
    }

    //startPeriodicCont = false;
    // periodic and continuous only once
    if (startPeriodicCont)
    {
        //command.productType = telemetry_telecommand::messages::DEM;
        //command.productType = telemetry_telecommand::messages::POINT_CLOUD;
        //command.productType = telemetry_telecommand::messages::DISTANCE;
        command.productType = telemetry_telecommand::messages::IMAGE;

        //command.productMode = telemetry_telecommand::messages::CONTINUOUS;
        command.productMode = telemetry_telecommand::messages::PERIODIC;
        command.usecPeriod = 4e6;

        startPeriodicCont = false;
        _telecommand_out.write( command );
    }
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
