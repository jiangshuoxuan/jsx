#include <graphenelib/asset.h>
#include <graphenelib/contract.hpp>
#include <graphenelib/contract_asset.hpp>
#include <graphenelib/crypto.h>
#include <graphenelib/dispatcher.hpp>
#include <graphenelib/global.h>
#include <graphenelib/multi_index.hpp>
#include <graphenelib/print.hpp>
#include <graphenelib/system.h>
#include <graphenelib/types.h>
#include <vector>
#include<cmath>

using namespace graphene;

static const uint64_t redpacket_asset_id = 1;//GXS

class redpacket : public contract
{
  public:
    redpacket(uint64_t id)
        : contract(id)
        , receivers(_self, _self)
        , records(_self, _self)
    {
    }

  

    // @abi action adddonnor 
     void adddonnor( std::string donnor_name,uint64_t donnor_age,uint64_t sex,std::string donnor_ID_card)
    {
        /*新建捐赠人的信息，以及受益人的空表，以及见证人的空表*/
        Donnor donnor_message;
        donnor_message.name=donnor_name;
        donnor_message.age=donnor_age;
        donnor_message.sex=sex;
        donnor_message.ID_card=donnor_ID_card;
     
        
        std::vector<Receiver> receiver_empty;
        std::vector<Notary_public> notary_public_empty;
        //获取当前用户的id
        uint64_t donnors = get_trx_sender();
        auto it = records.find(donnors);
        if (it == records.end())
        {//没找到该用户曾经创立过遗嘱,则新加入一个结点
            records.emplace(donnors, [&](auto &o ) 
            {
                o.packet_issuer = donnors;
                o.donnor_info=donnor_message;
                o.receiver_list=receiver_empty;
                o.Notary_public_list=notary_public_empty;
                o.event_accept=false;
            });
        }
            else
            {
                records.modify(it, 0, [&](auto &o) { o.donnor_info = donnor_message; });
            }
    }
    //@abi action addreceiver
    void addreceiver(std::vector<std::string> receiver_names,std::vector<contract_asset> receiver_amounts)
    {
        
        uint64_t donnor_owner = get_trx_sender();
        auto it = records.find(donnor_owner);
        graphene_assert(it != records.end(), "owner has no asset");
        
        int receivers_length=receiver_names.size();
        int amounts_length=receiver_amounts.size();
        graphene_assert(receivers_length==amounts_length,"receiver length is not match amount length");
        for(int i=0;i<receivers_length;i++)
        {
            int64_t account_id = get_account_id(receiver_names[i].c_str(), receiver_names[i].size());
            graphene_assert(account_id >= 0, "invalid account_name to_account");
            graphene_assert(receiver_amounts[i].amount > 0, "invalid amount");
            Receiver new_receiver;
            new_receiver.amount=receiver_amounts[i].amount;
            new_receiver.receiver_id=account_id;
            records.modify(it,0,[&](auto &o){o.receiver_list.push_back(new_receiver);});
            
            auto receiver_it=receivers.find(new_receiver.receiver_id);
            if(receiver_it==receivers.end())
            {
                receivers.emplace(account_id,[&](auto &o){
                    o.issuer=account_id;
                    o.receiver_info.push_back(new_receiver);
                    o.donnor_info.push_back();
                });
            }
            receivers.emplace()
           // records.modify(it,0,[&](auto &o){o.receiver_list.push_back()})
           /* for(int j=0;j<records.size();j++)
            {
                if(records[j].packet_issuer==donnor_owner) {
                    
                    break;
                }
                }
            }*/
            
        }
    }
/*  void add_notary_public_message(std::string donnor_owner)
    {
        uint64_t notary_public=get_trx_sender();
        uint64_t donnor_id = get_account_id(donnor_owner.c_str(), donnor_owner.size());
        graphene_assert(donnor_id >= 0, "invalid account_name to_account");
        auto it=testaments.find(donnor_id);
        graphene_assert(it != accounts.end(), "owner has no asset");
        records.modify(it,0,[&](auto &o){o.})
    }*/
  private:
  
  
   

    struct account {
        uint64_t    account_id;
        int64_t     amount;

        GRAPHENE_SERIALIZE(account, (account_id)(amount))
    };
    
 
    struct Donnor
    {//遗嘱人
        std::string name; 
        std::string ID_card;
        uint64_t sex;
        uint64_t age;
        GRAPHENE_SERIALIZE(Donnor, (name)(ID_card)(sex)(age))
    };
    
    struct Receiver 
     {//受益人
        uint64_t    receiver_id;
        int64_t     amount;
        GRAPHENE_SERIALIZE(Receiver, (receiver_id)(amount))
    };
   
     struct Notary_public
    {//公证人
        uint64_t   notary_public_id;
        bool check;
        GRAPHENE_SERIALIZE(Notary_public, (notary_public_id)(check))
    };

    //@abi table record i64
    struct record {
        uint64_t packet_issuer;
        Donnor donnor_info;
        std::vector<Receiver> receiver_list;
        std::vector<Notary_public>Notary_public_list;
        bool event_accept;
        uint64_t primary_key() const { return packet_issuer; }
        Donnor get_donnor_info() const{ }
        GRAPHENE_SERIALIZE(record, (packet_issuer)(donnor_info)(receiver_list)(Notary_public_list)(event_accept))

    };
    typedef graphene::multi_index<N(record), record> record_index;
   
    //@abi table receiver_view i64
    struct receiveview {
        uint64_t                issuer;
        Receiver                receiver_info;
        Donnor                  donnor_info;

        uint64_t primary_key() const { return issuer; };

        GRAPHENE_SERIALIZE(receiveview, (issuer)(receiver_info)(donnor_info))
    };
    typedef graphene::multi_index<N(receiveview), receiveview> receiver_view_index;
    receiver_view_index     receivers;
    record_index            records;
};
GRAPHENE_ABI(redpacket, (adddonnor)(addreceiver))
