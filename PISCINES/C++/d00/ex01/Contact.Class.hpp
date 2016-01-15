#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

class Contacts {

public:
		 Contacts( void );
		 ~Contacts( void );
	int	 getContactNb( void ) const;
	void add_a_contact( void );

	char	first_name[256];
	char	last_name[256];
	char	nickname[256];
	char	login[256];
	char	adress[256];
	char	email[256];
	char	phone[256];
	char	birthday[256];
	char	fav_meal[256];
	char	underwear[256];
	char	secret[256];

private:
	static int	_contactNb;
};

#endif
