#include <graphenelib/action.h>
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

#include<cmath>

using namespace graphene;

class testament
{
    private:
    
    enum sex_type{
        man,
        woman
    }
    
    struct donnor
    {
        std::string name; 
        int age;
        sex_type sex;
        std::string ID_card;
        GRAPHENE_SERIALIZE(donnor, (name)(age)(sex)(ID_card)(donnor_id))
    }
     struct receiver {
        uint64_t    receiver_id;
        int64_t     amount;
        GRAPHENE_SERIALIZE(receiver, (receiver_id_id)(amount))
    };
    //@abi table
    struct testament
    {
        uint64_t donnor_id;
        donnor donnor_info;
        std::vector<receiver> receiver_list;
        bool event_accept;
        bool die_happen;
        GRAPHENE_SERIALIZE(testament, (donnor_id)(donnor_info)(receiver_list)(event_accept))
    }
    typedef graphene::multi_index<N(testament), testament> testament_index;
    struct donnor_amount
    {
        donnor donnor_name;
        int64_t amount;
        GRAPHENE_SERIALIZE(donnor_amount, (donnor_name)(amount))
    }
    //@abi table
    struct receiver_list
    {
        uint64_t receiver_id;
        std::vector<donnor_amount> donnor_list;
         GRAPHENE_SERIALIZE(receiver_list, (receiver_id)(donnor_list))
    }
    typedef graphene::multi_index<N(receiver_list), receiver_list> receiver_list_index;
    testament_index testaments;
    receiver_list_index receivers;
   
    public:
    
    void add_donnor_message( std::string donnor_name,int donnor_age,int sex,std::string donnor_ID_card)
    {
        struct donnor donnor_message;
        donnor_message.name=donnor_name;
        donnor_message.age=donnor_age;
        donnor_message.sex=sex?man:woman;
        donnor_message.ID_card=donnor_ID_card;
        graphene_assert(donnor_message.age >= 0, "invalid donnor age");
        graphene_assert(donnor_message.sex >= 0&&donnor_message.sex<=1, "invalid donnor sex");
        std::vector<receiver> receiver_empty;
        //��ȡ��ǰ�û���id
        uint64_t donnor = get_trx_sender();
        auto it = testaments.find(donnor_id);
        if (it == testaments.end())
        {//û�ҵ����û���������������,���¼���һ�����
            testaments.emplace(donnor, [&](auto &o ) 
            {
                o.donnor_id = donnor;
                o.donnor_info.emplace_back(donnor_message);
                o.receiver_list=receiver_empty;
                o.event_accept=false;
                o.die_happen=false;
            };
        }
            else
            {
                testaments.modify(it, 0, [&](auto &o) { o.donnor_info = donnor_message; }
            }
    }
    
    bool check_donnor_in_table()
    {
        uint64_t donnor = get_trx_sender();
        
        auto it = testaments.find(donnor_id);
        if(it==testaments.end())
            return false;
        else return true;
    }
    

    void add_receiver_message(std::vector<std::string> receiver_names,std::vector<contract_asset> receiver_amounts)
    {
        
        uint64_t donnor_owner = get_trx_sender();
        auto it = testaments.find(donnor_owner);
        graphene_assert(it != accounts.end(), "owner has no asset");
        
        int receivers_length=receiver_names.size();
        int amounts_length=receiver_amounts.size();
        graphene_assert(receivers_length==amounts_length,"receiver length is not match amount length");
        for(int i=0;i<receivers_length;i++)
        {
            int64_t account_id = get_account_id(receiver_names[i].c_str(), receiver_names[i].size());
            graphene_assert(account_id >= 0, "invalid account_name to_account");
            graphene_assert(receiver_amounts[i].amount > 0, "invalid amount");
            
        }
        
    }
    
    void check_receiver_message()
    {
        
    }
    
    void check_Notary_public_message(std::string donnor_owner)
    {
        
    }

    cofigure()
    
}


GRAPHENE_ABI(redpacket, (issue)(open)(close))
