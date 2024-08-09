// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/AGD_BaseWeapon.h"

AAGD_BaseWeapon::AAGD_BaseWeapon() { PrimaryActorTick.bCanEverTick = false; }

// Called when the game starts or when spawned
void AAGD_BaseWeapon::BeginPlay() { Super::BeginPlay(); }

void AAGD_BaseWeapon::Tick(float DeltaTime) { Super::Tick(DeltaTime); }
