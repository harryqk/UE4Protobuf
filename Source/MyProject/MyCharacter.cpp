// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Harry1.pb.h"
#include "library.h"
#include "SCPPSocket/NetManager.h"
using namespace std;
using namespace tutorial;
using namespace scppsocket;
NetManager Mgr;
void OnServerMessageRead(int fd, const char* msg, int len);
void OnProtobufMessageRead(int fd, const char* msg, int len);
void OnServerMessageRead(int fd, const char *msg, int len)
{
	char* str = new char[len + 1];
	memcpy(str, msg, len);
	str[len] = '\0';
	printf("server read  fd:%d\n", fd);
	printf("server read  len:%d\n", len);
	printf("server read  msg:%s\n", str);
	UE_LOG(LogTemp, Warning, TEXT("fd:%d"), fd);
	UE_LOG(LogTemp, Warning, TEXT("len:%d"), len);
	UE_LOG(LogTemp, Warning, TEXT("msg:%s"), *FString(str));
	delete[] str;
}

void OnProtobufMessageRead(int fd, const char *msg, int len)
{
	char* str = new char[len + 1];
	memcpy(str, msg, len);
	str[len] = '\0';
	Harry1 example2;
	example2.ParseFromArray(str,len);

	UE_LOG(LogTemp, Warning, TEXT("1:%s"), *FString(example2.stringval().c_str()));
	//UE_LOG(LogTemp, Warning, TEXT("2:%s"), FString(example2.stringval().c_str()));
	UE_LOG(LogTemp, Warning, TEXT("3:%d"), example2.embeddedexample1().int32val());
	UE_LOG(LogTemp, Warning, TEXT("4:%s"), *FString(example2.embeddedexample1().stringval().c_str()));
	//printf("1:%s\n", example2.stringval());
	//printf("2:%s\n", example2.bytesval());
	//printf("3:%d\n", example2.embeddedexample1().int32val());
	//printf("4:%s\n", example2.embeddedexample1().stringval());

	for (int i = 0; i < example2.repeatedint32val().size(); i++)
	{
		//printf("5:%d\n", example2.repeatedint32val(i));
		UE_LOG(LogTemp, Warning, TEXT("5:%d"), example2.repeatedint32val(i));
	}

	for (int i = 0; i < example2.repeatedstringval().size(); i++)
	{
		//printf("6:%s\n", example2.repeatedstringval(i));
		UE_LOG(LogTemp, Warning, TEXT("6:%s"), *FString(example2.repeatedstringval(i).c_str()));
	}
	delete[] str;
}
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	
    UE_LOG(LogTemp, Warning, TEXT("Hello World"));
    Harry1 example1;
    example1.set_stringval("hello,world");
    example1.set_bytesval("are you ok?");

    Harry1_EmbeddedMessage* embeddedExample2 = new Harry1_EmbeddedMessage();

    embeddedExample2->set_int32val(1);
    embeddedExample2->set_stringval("embeddedInfo");
    example1.set_allocated_embeddedexample1(embeddedExample2);

    example1.add_repeatedint32val(2);
    example1.add_repeatedint32val(3);
    example1.add_repeatedstringval("repeated1");
    example1.add_repeatedstringval("repeated2");
    string str;
    example1.SerializeToString(&str);
    Harry1 example2;
    example2.ParseFromString(str);

    UE_LOG(LogTemp, Warning, TEXT("1:%s"), *FString(example2.stringval().c_str()));
    //UE_LOG(LogTemp, Warning, TEXT("2:%s"), FString(example2.stringval().c_str()));
    UE_LOG(LogTemp, Warning, TEXT("3:%d"), example2.embeddedexample1().int32val());
    UE_LOG(LogTemp, Warning, TEXT("4:%s"), *FString(example2.embeddedexample1().stringval().c_str()));
    //printf("1:%s\n", example2.stringval());
    //printf("2:%s\n", example2.bytesval());
    //printf("3:%d\n", example2.embeddedexample1().int32val());
    //printf("4:%s\n", example2.embeddedexample1().stringval());

    for (int i = 0; i < example2.repeatedint32val().size(); i++)
    {
        //printf("5:%d\n", example2.repeatedint32val(i));
        UE_LOG(LogTemp, Warning, TEXT("5:%d"), example2.repeatedint32val(i));
    }

    for (int i = 0; i < example2.repeatedstringval().size(); i++)
    {
        //printf("6:%s\n", example2.repeatedstringval(i));
        UE_LOG(LogTemp, Warning, TEXT("6:%s"), *FString(example2.repeatedstringval(i).c_str()));
    }

	//GoString strx;
	//strx = Hello();   
	//Print_a();
	//UE_LOG(LogTemp, Warning, TEXT("7:%s"), *FString(strx.p));

	Mgr = NetManager();
	Mgr.SetOnServerMessageRead(OnProtobufMessageRead);
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::StopServer_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("StopServer_Implementation"));
	Mgr.StopTCPCServer();
	Mgr.Clear();
}

void AMyCharacter::StartServer_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("StartServer_Implementation"));
	Mgr.StartTCPServer(1500, 6);
}

