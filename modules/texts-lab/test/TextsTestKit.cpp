#include <gtest/gtest.h>
#include "include/TText.h"


void test_text(TText *t)
{
	t->Reset();
	t->SetLine("1.1. Полиномы");
	t->InsDownSection("2. Структура");
	t->InsDownLine("1. Определение");
	t->InsNextLine("1.2. Тексты");
	
	t->GoNextLink();
	t->InsDownSection("2. Структура");
	t->InsDownLine("1. Определение");
	t->Reset();
}


TEST(TTextLink_test, can_initialize_memory_system)
{
	ASSERT_NO_THROW(TTextLink::InitMemSystem());
	TTextLink::DelMemSystem();
}

TEST(TTextLink_test, cant_initialize_memory_system_with_negative_size)
{
	ASSERT_ANY_THROW(TTextLink::InitMemSystem(-12));
}

TEST(TTextLink_test, cant_call_twice_finction)
{
	TTextLink::InitMemSystem();
	ASSERT_ANY_THROW(TTextLink::InitMemSystem());
	TTextLink::DelMemSystem();
}

TEST(TTextLink_test, can_create_zero_text_link)
{
	ASSERT_NO_THROW(TTextLink());
}

TEST(TTextLink_test, can_create_text_link)
{
	TTextLink::InitMemSystem();

	char str[TEXT_LINE_LENGTH - 10];

	for (int i = 0; i < TEXT_LINE_LENGTH - 10; i++) str[i] = 'u';
	str[TEXT_LINE_LENGTH - 11] = '\0';
	ASSERT_NO_THROW(TTextLink(str));
	
	TTextLink::DelMemSystem();
}

TEST(TTextLink_test, cant_create_text_link_with_longer_string)
{
	TTextLink::InitMemSystem();

	char str[TEXT_LINE_LENGTH + 10];

	for (int i = 0; i < TEXT_LINE_LENGTH + 10; i++) str[i] = 'u';
	str[TEXT_LINE_LENGTH + 9] = '\0';

	ASSERT_ANY_THROW(TTextLink((std::string)str));
	
	TTextLink::DelMemSystem();
}

TEST(TText_test, can_create_text)
{
	TTextLink::InitMemSystem();

	TTextLink ptl("hey", nullptr, nullptr);
	ASSERT_NO_THROW(TText t(&ptl));
	TTextLink::DelMemSystem();

}

TEST(TText_test, can_create_zero_text)
{
	TTextLink::InitMemSystem();

	ASSERT_NO_THROW(TText t);

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_copy_text)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	ASSERT_NO_THROW(TText t2(t1));

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_set_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);
	ASSERT_NO_THROW(t1.SetLine("Hello"));

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_get_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	ASSERT_NO_THROW(t1.GetLine());

	TTextLink::DelMemSystem();
}

TEST(TText_test, text_and_its_copy_have_different_memory)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	TText t2(t1);

	t2.SetLine("Hello");

	EXPECT_NE(t2.GetLine(), t1.GetLine());

	TTextLink::DelMemSystem();
}

TEST(TText_test, set_and_get_some_value)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);
	t1.SetLine("Hello");

	EXPECT_EQ("Hello", t1.GetLine());

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_set_string_by_using_data_type_Tstr)
{
	TTextLink::InitMemSystem();

	TStr s = "Hello";
	TText t;
	test_text(&t);
	t.SetLine(s);
	ASSERT_NO_THROW(t.SetLine(s));

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_set_string_by_using_data_type_string)
{
	TTextLink::InitMemSystem();

	string s = "Hello";
	TText t;
	test_text(&t);

	ASSERT_NO_THROW(t.SetLine(s));

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_insert_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");
	t1.InsDownLine("Hello");
	t1.GoDownLink();

	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_down_line_if_current_link_is_null)
{
	TTextLink::InitMemSystem();
	TText t1;
	t1.InsDownLine("Hello");

	EXPECT_EQ(t1.GetRetCode(), TextError);
	TTextLink::DelMemSystem();
}

TEST(TText_test, can_insert_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");
	t1.InsDownLine("Hello");
	t1.InsDownSection("World");

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), "World");

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_down_section_if_current_link_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.InsDownSection("Hello");

	EXPECT_EQ(t1.GetRetCode(), TextError);
	TTextLink::DelMemSystem();
}

TEST(TText_test, can_insert_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");
	t1.InsNextLine("Hello");
	t1.GoNextLink();

	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_next_line_if_current_link_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.InsNextLine("Hello");

	EXPECT_EQ(t1.GetRetCode(), TextError);
	TTextLink::DelMemSystem();
}

TEST(TText_test, can_insert_next_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");
	t1.InsNextLine("Hello");
	t1.InsNextSection("World");

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), "World");

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_next_section_if_current_link_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.InsNextSection("Hello");

	EXPECT_EQ(t1.GetRetCode(), TextError);

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_delete_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");
	t1.InsDownLine("Hello");
	t1.InsDownLine("World");

	t1.DelDownLine();

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, down_line_cant_be_deleted_if_it_has_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");
	t1.InsDownLine("Hello");
	t1.InsDownLine("World");
	t1.InsDownSection(":)");

	t1.DelDownLine();

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), ":)");

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_line_is_correct_if_text_dont_have_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");

	t1.DelDownLine();

	EXPECT_EQ(t1.GetRetCode(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_line_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelDownLine();

	EXPECT_EQ(t1.GetRetCode(), TextError);

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_delete_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	t1.SetLine("begin");
	t1.InsDownLine("Hello");
	t1.InsDownSection("World");

	t1.DelDownSection();

	t1.GoDownLink();
	EXPECT_EQ(t1.GetRetCode(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_section_is_correct_if_text_dont_have_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");

	t1.DelDownSection();

	EXPECT_EQ(t1.GetRetCode(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_section_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelDownSection();

	EXPECT_EQ(t1.GetRetCode(), TextError);

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_delete_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");
	t1.InsNextLine("Hello");
	t1.InsNextLine("World");

	t1.DelNextLine();

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, next_line_cant_be_deleted_if_it_has_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");
	t1.InsNextLine("Hello");
	t1.GoNextLink();
	t1.InsDownLine("World");
	t1.GoFirstLink();

	t1.DelNextLine();

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), "Hello");

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_line_is_correct_if_text_dont_have_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");

	t1.DelNextLine();

	EXPECT_EQ(t1.GetRetCode(), TextNoNext);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_line_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelNextLine();

	EXPECT_EQ(t1.GetRetCode(), TextError);

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_delete_next_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");
	t1.InsNextLine("Hello");
	t1.GoNextLink();
	t1.InsDownLine("World");
	t1.InsNextLine(":)");
	t1.GoFirstLink();

	t1.DelNextSection();

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), ":)");

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_section_is_correct_if_text_dont_have_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	t1.SetLine("begin");

	t1.DelNextSection();

	EXPECT_EQ(t1.GetRetCode(), TextNoNext);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_section_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();
	TText t1;
	t1.SetLine("begin");

	t1.DelNextSection();

	EXPECT_EQ(t1.GetRetCode(), TextError);
	TTextLink::DelMemSystem();
}

TEST(TText_test, can_go_first_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);
	t1.Reset();
	t1.SetLine("begin");

	EXPECT_EQ(t1.GoFirstLink(), TextOk);
	EXPECT_EQ("begin", t1.GetLine());;

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_go_down_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	EXPECT_EQ(t1.GoDownLink(), TextOk);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoDownLink_is_correct_if_current_link_dont_have_down_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();

	EXPECT_EQ(t1.GoDownLink(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoDownLink_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();

	TText t1;

	EXPECT_EQ(t1.GoDownLink(), TextError);

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_go_next_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	EXPECT_EQ(t1.GoNextLink(), TextOk);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoNextLink_is_correct_if_current_link_dont_have_next_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.Reset();
	EXPECT_EQ(t1.GoNextLink(), TextNoNext);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoNextLink_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();
	TText t1;

	EXPECT_EQ(t1.GoNextLink(), TextError);
	TTextLink::DelMemSystem();
}

TEST(TText_test, can_go_prev_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	t1.GoNextLink();
	EXPECT_EQ(t1.GoPrevLink(), TextOk);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoPrevLink_is_correct_if_current_link_dont_have_prev_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);

	EXPECT_EQ(t1.GoPrevLink(), TextNoPrev);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoPrevLink_is_correct_if_current_line_is_null)
{
	TTextLink::InitMemSystem();
	TText t1;

	EXPECT_EQ(t1.GoPrevLink(), TextError);
	TTextLink::DelMemSystem();
}
