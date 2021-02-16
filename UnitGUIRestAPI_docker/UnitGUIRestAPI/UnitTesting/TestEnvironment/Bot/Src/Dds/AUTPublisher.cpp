// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file AUTPublisher.cpp
 *
 */

#include "DataPacketPubSubTypes.h"
#include "AUTUtility.h"

/*From .h file*/
#include <fastdds/dds/topic/Topic.hpp>

/*From .cpp file*/
#include <fastdds/rtps/transport/TCPv4TransportDescriptor.h>
#include <fastrtps/utils/IPLocator.h>


#include <fastrtps/Domain.h>
#include <fastrtps/log/Log.h>

#include <string>

#include "optionparser.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>


using namespace eprosima::fastdds::dds;
using namespace eprosima::fastdds::rtps;

class AUTPublisher
{
private:

    DataPacket hello_;

    DomainParticipant* participant_;

    Publisher* publisher_;

    Topic* topic_;

    DataWriter* writer_;

    TypeSupport type_;

    AUTUtility* aut;
    
    bool stop_;

    class PubListener : public DataWriterListener
    {
    public:

        PubListener()
            : matched_(0)
            , first_connected_(false)
        {
        }

        ~PubListener() override
        {
        }

        void on_publication_matched(
                DataWriter*,
                const PublicationMatchedStatus& info) override
        {
            if (info.current_count_change == 1)
            {
                matched_ = info.total_count;
                std::cout << "Publisher matched." << std::endl;
            }
            else if (info.current_count_change == -1)
            {
                matched_ = info.total_count;
                std::cout << "Publisher unmatched." << std::endl;
            }
            else
            {
                std::cout << info.current_count_change
                        << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
            }
        }

        std::atomic_int matched_;
        
        bool first_connected_;

    } listener_;

public:

    AUTPublisher(AUTUtility* c)
        : participant_(nullptr)
        , publisher_(nullptr)
        , topic_(nullptr)
        , writer_(nullptr)
        , type_(new DataPacketPubSubType())
	, aut(c)
    {
    }

    virtual ~AUTPublisher()
    {
        if (writer_ != nullptr)
        {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_ != nullptr)
        {
            participant_->delete_publisher(publisher_);
        }
        if (topic_ != nullptr)
        {
            participant_->delete_topic(topic_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    //!Initialize the publisher
    bool init(
        const std::string& wan_ip,
        unsigned short port,
        bool use_tls,
        const std::vector<std::string>& whitelist)
    {
        stop_ = false;
	hello_.index(0);
        hello_.message(aut->getResultMsgPub());

        DomainParticipantQos participantQos;
        participantQos.name("Rpi_publisher");

        participantQos.wire_protocol().builtin.discovery_config.leaseDuration = eprosima::fastrtps::c_TimeInfinite;
    	participantQos.wire_protocol().builtin.discovery_config.leaseDuration_announcementperiod =
            eprosima::fastrtps::Duration_t(5, 0);

    	participantQos.transport().use_builtin_transports = false;
    

	std::shared_ptr<TCPv4TransportDescriptor> descriptor = std::make_shared<TCPv4TransportDescriptor>();

	for (std::string ip : whitelist)
	{
		descriptor->interfaceWhiteList.push_back(ip);
		std::cout << "Whitelisted " << ip << std::endl;
	}

	if (use_tls)
	{
		using TLSOptions = TCPTransportDescriptor::TLSConfig::TLSOptions;
		descriptor->apply_security = true;
		descriptor->tls_config.password = "test";
		descriptor->tls_config.cert_chain_file = "server.pem";
		descriptor->tls_config.private_key_file = "server.pem";
		descriptor->tls_config.tmp_dh_file = "dh2048.pem";
		descriptor->tls_config.add_option(TLSOptions::DEFAULT_WORKAROUNDS);
		descriptor->tls_config.add_option(TLSOptions::SINGLE_DH_USE);
		descriptor->tls_config.add_option(TLSOptions::NO_SSLV2);
	}

	descriptor->wait_for_tcp_negotiation = false;
	descriptor->sendBufferSize = 0;
	descriptor->receiveBufferSize = 0;

	if (!wan_ip.empty())
	{
		descriptor->set_WAN_address(wan_ip);
		std::cout << wan_ip << ":" << port << std::endl;
	}
	descriptor->add_listener_port(port);
	participantQos.transport().user_transports.push_back(descriptor);

	
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

        if (participant_ == nullptr)
        {
            return false;
        }

        // Register the Type
        type_.register_type(participant_);

        // Create the publications Topic
        topic_ = participant_->create_topic("ResultCmd", "DataPacket", TOPIC_QOS_DEFAULT);

        if (topic_ == nullptr)
        {
            return false;
        }

        // Create the Publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

        if (publisher_ == nullptr)
        {
            return false;
        }

        //CREATE THE DATAWRITER
	DataWriterQos wqos;
	wqos.history().kind = KEEP_LAST_HISTORY_QOS;
	wqos.history().depth = 30;
	wqos.resource_limits().max_samples = 50;
	wqos.resource_limits().allocated_samples = 20;
	wqos.reliable_writer_qos().times.heartbeatPeriod.seconds = 2;
	wqos.reliable_writer_qos().times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
	wqos.reliability().kind = RELIABLE_RELIABILITY_QOS;

	writer_ = publisher_->create_datawriter(topic_, wqos, &listener_);

        if (writer_ == nullptr)
        {
            return false;
        }
        return true;
    }

    //!Send a publication
    bool publish(bool waitForListener = true)
    {
	hello_.message(aut->getResultMsgPub());
        if (listener_.first_connected_ || !waitForListener || listener_.matched_ > 0)
        {
            hello_.index(hello_.index() + 1);
            writer_->write(&hello_);
            return true;
        }
        return false;
    }

    //!Run the Publisher
    void run(
        uint32_t samples,
        long sleep_ms)
    {
	//std::thread thread(&HelloWorldPublisher::runThread, this, samples, sleep_ms);
        uint32_t samples_sent = 0;
        while (!aut->m_stop)
        {
	  if(aut->getResultMsgPub() != "")
	  {
            if (publish())
            {
                samples_sent++;
                std::cout << "Message: " << hello_.message() << " with index: " << hello_.index()
                            << " SENT" << std::endl;
		aut->setResultMsgPub("");

            }
	  }
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

        void runThread(
        uint32_t samples,
        long sleep_ms)
	{
	    if (samples == 0)
	    {
		while (!stop_)
		{
		    if (publish(false))
		    {
		        //logError(HW, "SENT " <<  hello_.index());
		        std::cout << "[RTCP] Message: " << hello_.message() << " with index: "
		                  << hello_.index() << " SENT" << std::endl;
		    }
		    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
		}
	    }
	    else
	    {
		for (uint32_t i = 0; i < samples; ++i)
		{
		    if (!publish())
		    {
		        --i;
		    }
		    else
		    {
		        std::cout << "[RTCP] Message: " << hello_.message() << " with index: "
		                  << hello_.index() << " SENT" << std::endl;
		    }
		    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
		}
	    }
	}
};


struct Arg: public option::Arg
{
    static void print_error(const char* msg1, const option::Option& opt, const char* msg2)
    {
        fprintf(stderr, "%s", msg1);
        fwrite(opt.name, opt.namelen, 1, stderr);
        fprintf(stderr, "%s", msg2);
    }

    static option::ArgStatus Unknown(const option::Option& option, bool msg)
    {
        if (msg) print_error("Unknown option '", option, "'\n");
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus Required(const option::Option& option, bool msg)
    {
        if (option.arg != 0 && option.arg[0] != 0)
        return option::ARG_OK;

        if (msg) print_error("Option '", option, "' requires an argument\n");
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus Numeric(const option::Option& option, bool msg)
    {
        char* endptr = 0;
        if (option.arg != 0 && strtol(option.arg, &endptr, 10))
        {
        }
        if (endptr != option.arg && *endptr == 0)
        {
            return option::ARG_OK;
        }

        if (msg)
        {
            print_error("Option '", option, "' requires a numeric argument\n");
        }
        return option::ARG_ILLEGAL;
    }

    static option::ArgStatus String(const option::Option& option, bool msg)
    {
        if (option.arg != 0)
        {
            return option::ARG_OK;
        }
        if (msg)
        {
            print_error("Option '", option, "' requires a numeric argument\n");
        }
        return option::ARG_ILLEGAL;
    }
};



enum  optionIndex {
    UNKNOWN_OPT,
    HELP,
    SAMPLES,
    INTERVAL,
    IP,
    PORT,
    TLS,
    WHITELIST
};


const option::Descriptor usage[] = {
    { UNKNOWN_OPT, 0,"", "",                Arg::None,
        "Usage: HelloWorldExampleTCP <publisher|subscriber>\n\nGeneral options:" },
    { HELP,    0,"h", "help",               Arg::None,      "  -h \t--help  \tProduce help message." },
    { TLS, 0, "t", "tls",          Arg::None,      "  -t \t--tls \tUse TLS." },
    { WHITELIST, 0, "w", "whitelist",       Arg::String,    "  -w \t--whitelist \tUse Whitelist." },

    { UNKNOWN_OPT, 0,"", "",                Arg::None,      "\nPublisher options:"},
    { SAMPLES,0,"s","samples",              Arg::Numeric,
        "  -s <num>, \t--samples=<num>  \tNumber of samples (0, default, infinite)." },
    { INTERVAL,0,"i","interval",            Arg::Numeric,
        "  -i <num>, \t--interval=<num>  \tTime between samples in milliseconds (Default: 100)." },
    { IP,0,"a","address",                   Arg::String,
        "  -a <address>, \t--address=<address> \tPublic IP Address of the publisher (Default: None)." },
    { PORT, 0, "p", "port",                 Arg::Numeric,
        "  -p <num>, \t--port=<num>  \tPhysical Port to listening incoming connections (Default: 5100)." },

    { UNKNOWN_OPT, 0,"", "",                Arg::None,      "\nSubscriber options:"},
    { IP,0,"a","address",                   Arg::String,
        "  -a <address>, \t--address=<address> \tIP Address of the publisher (Default: 127.0.0.1)." },
    { PORT, 0, "p", "port",                 Arg::Numeric,
        "  -p <num>, \t--port=<num>  \tPhysical Port where the publisher is listening for connections (Default: 5100)." },

    { 0, 0, 0, 0, 0, 0 }
};


void PublisherMain(AUTUtility* c)
{

int argc = 6;
int columns;
char *argv[] = {"Dummy", "publisher", "-a", "192.168.43.242", "-p", "5100"};



#if defined(_WIN32)
    char* buf = nullptr;
    size_t sz = 0;
    if (_dupenv_s(&buf, &sz, "COLUMNS") == 0 && buf != nullptr)
    {
        columns = strtol(buf, nullptr, 10);
        free(buf);
    }
    else
    {
        columns = 80;
    }
#else
    columns = getenv("COLUMNS") ? atoi(getenv("COLUMNS")) : 80;
#endif

    std::cout << "Starting " << std::endl;
    int type = 1;
    int count = 0;
    long sleep = 100;
    std::string wan_ip;
    int port = 5100;
    bool use_tls = false;
    std::vector<std::string> whitelist;

    if (argc > 1)
    {
        if (strcmp(argv[1], "publisher") == 0)
        {
            type = 1;
        }
        else if (strcmp(argv[1], "subscriber") == 0)
        {
            type = 2;
        }

        //argc -= (argc > 0);
        //argv += (argc > 0); // skip program name argv[0] if present
        --argc;
        // ++argv; // skip pub/sub argument
         
         --argc;
         //++argv; 
         
        option::Stats stats(usage, argc, (char**)(&argv[2]));
        std::vector<option::Option> options(stats.options_max);
        std::vector<option::Option> buffer(stats.buffer_max);
        option::Parser parse(usage, argc, (char**)(&argv[2]), &options[0], &buffer[0]);

        if (parse.error())
        {
            //return 1;
        }

        if (options[HELP])
        {
            option::printUsage(fwrite, stdout, usage, columns);
            //return 0;
        }

        for (int i = 0; i < parse.optionsCount(); ++i)
        {
            option::Option& opt = buffer[i];
            switch (opt.index())
            {
                case HELP:
                    // not possible, because handled further above and exits the program
                    break;

                case SAMPLES:
                    count = strtol(opt.arg, nullptr, 10);
                    break;

                case INTERVAL:
                    sleep = strtol(opt.arg, nullptr, 10);
                    break;

                case IP:
                {
                    if (opt.arg != nullptr)
                    {
                        wan_ip = std::string(opt.arg);
                    }
                    else
                    {
                        option::printUsage(fwrite, stdout, usage, columns);
                        //return 0;
                    }
                    break;
                }

                case PORT:
                    port = strtol(opt.arg, nullptr, 10);
                    break;

                case TLS:
                    use_tls = true;
                    break;

                case WHITELIST:
                    whitelist.emplace_back(opt.arg);
                    break;

                case UNKNOWN_OPT:
                    option::printUsage(fwrite, stdout, usage, columns);
                    //return 0;
                    break;
            }
        }
    }
    else
    {
        option::printUsage(fwrite, stdout, usage, columns);
        //return 0;
    }


  
    {
        AUTPublisher* mypub = new AUTPublisher(c);
        if (mypub->init(wan_ip, static_cast<uint16_t>(port), use_tls, whitelist))
        {
            mypub->run(count, sleep);
        }
        delete mypub;
    }
}
