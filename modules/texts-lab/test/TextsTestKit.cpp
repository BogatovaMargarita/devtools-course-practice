#include <gtest/gtest.h>
#include "include/TText.h"

#define TEMP_LINE "Hello"
#define TEMP_LINE1 "World"
#define TEMP_LINE2 ":)"

void test_text(TText *t)
{
	t->SetLine("1.1. Ïîëèíîìû");
	t->InsDownSection("2. Ñòðóêòóðà");
	t->InsDownLine("1. Îïðåäåëåíèå");
	t->InsNextLine("1.2. Òåêñòû");
	t->Reset();
	t->GoNextLink();
	t->InsDownSection("2. Ñòðóêòóðà");
	t->InsDownLine("1. Îïðåäåëåíèå");
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
	ASSERT_NO_THROW(t1.SetLine(TEMP_LINE));

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

	t2.SetLine(TEMP_LINE);

	EXPECT_NE(t2.GetLine(), t1.GetLine());

	TTextLink::DelMemSystem();
}

TEST(TText_test, set_and_get_some_value)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);
	t1.SetLine(TEMP_LINE);

	EXPECT_EQ(TEMP_LINE, t1.GetLine());

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_set_string_by_using_data_type_Tstr)
{
	TTextLink::InitMemSystem();

	TStr s = TEMP_LINE;
	TText t;
	test_text(&t);
	t.SetLine(s);
	ASSERT_NO_THROW(t.SetLine(s));

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_set_string_by_using_data_type_string)
{
	TTextLink::InitMemSystem();

	string s = TEMP_LINE;
	TText t;
	test_text(&t);

	ASSERT_NO_THROW(t.SetLine(s));

	TTextLink::DelMemSystem();
}

TEST(TText_test, can_insert_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsDownLine(TEMP_LINE);
	t1.GoDownLink();

	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_down_line_if_current_link_is_null)
{
	TText t1;
	t1.InsDownLine(TEMP_LINE);

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_insert_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsDownLine(TEMP_LINE);
	t1.InsDownSection(TEMP_LINE1);

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE1);

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_down_section_if_current_link_is_null)
{
	TText t1;
	t1.InsDownSection(TEMP_LINE);

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_insert_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsNextLine(TEMP_LINE);
	t1.GoNextLink();

	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_next_line_if_current_link_is_null)
{
	TText t1;
	t1.InsNextLine(TEMP_LINE);

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_insert_next_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsNextLine(TEMP_LINE);
	t1.InsNextSection(TEMP_LINE1);

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE1);

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, cant_insert_next_section_if_current_link_is_null)
{
	TText t1;
	t1.InsNextSection(TEMP_LINE);

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_delete_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsDownLine(TEMP_LINE);
	t1.InsDownLine(TEMP_LINE1);

	t1.DelDownLine();

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, down_line_cant_be_deleted_if_it_has_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsDownLine(TEMP_LINE);
	t1.InsDownLine(TEMP_LINE1);
	t1.InsDownSection(TEMP_LINE2);

	t1.DelDownLine();

	t1.GoDownLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE2);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_line_is_correct_if_text_dont_have_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelDownLine();

	EXPECT_EQ(t1.GetRetCode(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_line_is_correct_if_current_line_is_null)
{
	TText t1;
	t1.SetLine("begin");

	t1.DelDownLine();

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_delete_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsDownLine(TEMP_LINE);
	t1.InsDownSection(TEMP_LINE1);

	t1.DelDownSection();

	t1.GoDownLink();
	EXPECT_EQ(t1.GetRetCode(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_section_is_correct_if_text_dont_have_down_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelDownSection();

	EXPECT_EQ(t1.GetRetCode(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_down_section_is_correct_if_current_line_is_null)
{
	TText t1;
	t1.SetLine("begin");

	t1.DelDownSection();

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_delete_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsNextLine(TEMP_LINE);
	t1.InsNextLine(TEMP_LINE1);

	t1.DelNextLine();

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, next_line_cant_be_deleted_if_it_has_down_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsNextLine(TEMP_LINE);
	t1.GoNextLink();
	t1.InsDownLine(TEMP_LINE1);
	t1.GoFirstLink();

	t1.DelNextLine();

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_line_is_correct_if_text_dont_have_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelNextLine();

	EXPECT_EQ(t1.GetRetCode(), TextNoNext);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_line_is_correct_if_current_line_is_null)
{
	TText t1;
	t1.SetLine("begin");

	t1.DelNextLine();

	EXPECT_EQ(t1.GetRetCode(), TextError);
}

TEST(TText_test, can_delete_next_section)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");
	t1.InsNextLine(TEMP_LINE);
	t1.GoNextLink();
	t1.InsDownLine(TEMP_LINE1);
	t1.InsNextLine(TEMP_LINE2);
	t1.GoFirstLink();

	t1.DelNextSection();

	t1.GoNextLink();
	EXPECT_EQ(t1.GetLine(), TEMP_LINE2);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_section_is_correct_if_text_dont_have_next_line)
{
	TTextLink::InitMemSystem();

	TText t1;
	t1.SetLine("begin");

	t1.DelNextSection();

	EXPECT_EQ(t1.GetRetCode(), TextNoNext);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_deletion_next_section_is_correct_if_current_line_is_null)
{
	TText t1;
	t1.SetLine("begin");

	t1.DelNextSection();

	EXPECT_EQ(t1.GetRetCode(), TextError);
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

TEST(TText_test, cant_go_first_link_if_text_dont_have_memory)
{
	TText t1;
	EXPECT_EQ(t1.GoFirstLink(), TextNoMem);
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

	EXPECT_EQ(t1.GoDownLink(), TextNoDown);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoDownLink_is_correct_if_current_line_is_null)
{
	TText t1;

	EXPECT_EQ(t1.GoDownLink(), TextError);
}

TEST(TText_test, can_go_next_link)
{
	TTextLink::InitMemSystem();

	TText t1;
	test_text(&t1);
	t1.Reset();

	EXPECT_EQ(t1.GoNextLink(), TextOk);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoNextLink_is_correct_if_current_link_dont_have_next_link)
{
	TTextLink::InitMemSystem();

	TText t1;

	EXPECT_EQ(t1.GoNextLink(), TextNoNext);

	TTextLink::DelMemSystem();
}

TEST(TText_test, call_function_GoNextLink_is_correct_if_current_line_is_null)
{
	TText t1;

	EXPECT_EQ(t1.GoNextLink(), TextError);
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
	TText t1;

	EXPECT_EQ(t1.GoPrevLink(), TextError);
}
